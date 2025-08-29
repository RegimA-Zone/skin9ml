#!/usr/bin/env python3
"""
COSING Database Converter
Converts COSING cosmetic ingredients data from Excel/TSV to optimized SQLite database
for SkinTwin project integration.
"""

import pandas as pd
import sqlite3
import sys
import os
from pathlib import Path
import re
from datetime import datetime

def clean_text(text):
    """Clean text data by removing extra whitespace and special characters."""
    if pd.isna(text) or text is None:
        return None
    
    # Remove leading \xa0 (non-breaking space) and other whitespace
    text = str(text).strip()
    if text.startswith('\xa0'):
        text = text[1:].strip()
    
    # Replace empty strings with None
    if text == '' or text == '-':
        return None
        
    return text

def parse_multiple_values(value_str, separator='/'):
    """Parse multiple values separated by a delimiter."""
    if not value_str:
        return []
    
    values = []
    for val in value_str.split(separator):
        cleaned = clean_text(val)
        if cleaned:
            values.append(cleaned)
    return values

def parse_functions(function_str):
    """Parse comma-separated function values."""
    if not function_str:
        return []
    
    functions = []
    for func in function_str.split(','):
        cleaned = clean_text(func)
        if cleaned:
            functions.append(cleaned)
    return functions

def convert_date(date_str):
    """Convert date string to SQLite date format."""
    if not date_str:
        return None
    
    try:
        # Parse DD/MM/YYYY format
        dt = datetime.strptime(date_str, '%d/%m/%Y')
        return dt.strftime('%Y-%m-%d')
    except:
        return date_str  # Return as-is if parsing fails

def create_database(db_path, schema_path):
    """Create SQLite database with schema."""
    print(f"Creating database: {db_path}")
    
    # Remove existing database
    if os.path.exists(db_path):
        os.remove(db_path)
    
    # Create database and apply schema
    conn = sqlite3.connect(db_path)
    
    with open(schema_path, 'r') as f:
        schema_sql = f.read()
    
    # Execute schema in chunks (SQLite doesn't handle multiple statements well)
    statements = schema_sql.split(';')
    for statement in statements:
        statement = statement.strip()
        if statement:
            try:
                conn.execute(statement)
            except sqlite3.Error as e:
                print(f"Warning: Error executing statement: {e}")
                print(f"Statement: {statement[:100]}...")
    
    conn.commit()
    return conn

def load_cosing_data(tsv_path):
    """Load COSING data from TSV file."""
    print(f"Loading data from: {tsv_path}")
    
    df = pd.read_csv(tsv_path, sep='\t', dtype=str, keep_default_na=False)
    print(f"Loaded {len(df)} records")
    
    # Clean column names
    df.columns = [col.strip() for col in df.columns]
    
    return df

def populate_functions(conn, df):
    """Populate functions lookup table."""
    print("Populating functions table...")
    
    all_functions = set()
    
    # Extract all unique functions
    for func_str in df['Function']:
        if func_str and func_str != '':
            functions = parse_functions(func_str)
            all_functions.update(functions)
    
    print(f"Found {len(all_functions)} unique functions")
    
    # Insert functions
    for func in sorted(all_functions):
        conn.execute(
            "INSERT OR IGNORE INTO functions (function_name) VALUES (?)",
            (func,)
        )
    
    conn.commit()

def populate_restrictions(conn, df):
    """Populate restrictions lookup table."""
    print("Populating restrictions table...")
    
    restrictions = set()
    for restriction in df['Restriction']:
        cleaned = clean_text(restriction)
        if cleaned:
            restrictions.add(cleaned)
    
    print(f"Found {len(restrictions)} unique restrictions")
    
    for restriction in sorted(restrictions):
        conn.execute(
            "INSERT OR IGNORE INTO restrictions (restriction_code) VALUES (?)",
            (restriction,)
        )
    
    conn.commit()

def populate_ingredients(conn, df):
    """Populate main ingredients table."""
    print("Populating ingredients table...")
    
    cursor = conn.cursor()
    
    for _, row in df.iterrows():
        # Clean and prepare data
        cosing_ref = int(row['COSING Ref No']) if row['COSING Ref No'] else None
        inci_name = clean_text(row['INCI name'])
        inn_name = clean_text(row['INN name'])
        ph_eur_name = clean_text(row['Ph.\xa0Eur. Name'])
        cas_no = clean_text(row['CAS No'])
        ec_no = clean_text(row['EC No'])
        chemical_desc = clean_text(row['Chem/IUPAC Name / Description'])
        restriction = clean_text(row['Restriction'])
        update_date = convert_date(row['Update Date'])
        
        # Insert ingredient
        cursor.execute("""
            INSERT OR REPLACE INTO ingredients 
            (cosing_ref_no, inci_name, inn_name, ph_eur_name, cas_no, ec_no, 
             chemical_description, restriction, update_date)
            VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)
        """, (cosing_ref, inci_name, inn_name, ph_eur_name, cas_no, ec_no,
              chemical_desc, restriction, update_date))
        
        # Handle multiple CAS numbers
        if cas_no:
            cas_numbers = parse_multiple_values(cas_no, '/')
            for i, cas in enumerate(cas_numbers):
                if cas and cas != '-':
                    cursor.execute("""
                        INSERT INTO cas_numbers (ingredient_ref, cas_number, is_primary)
                        VALUES (?, ?, ?)
                    """, (cosing_ref, cas, i == 0))
        
        # Handle multiple EC numbers
        if ec_no:
            ec_numbers = parse_multiple_values(ec_no, '/')
            for i, ec in enumerate(ec_numbers):
                if ec and ec != '-':
                    cursor.execute("""
                        INSERT INTO ec_numbers (ingredient_ref, ec_number, is_primary)
                        VALUES (?, ?, ?)
                    """, (cosing_ref, ec, i == 0))
        
        # Handle functions
        if row['Function']:
            functions = parse_functions(row['Function'])
            for func in functions:
                # Get function ID
                cursor.execute("SELECT id FROM functions WHERE function_name = ?", (func,))
                func_result = cursor.fetchone()
                if func_result:
                    func_id = func_result[0]
                    cursor.execute("""
                        INSERT OR IGNORE INTO ingredient_functions (ingredient_ref, function_id)
                        VALUES (?, ?)
                    """, (cosing_ref, func_id))
    
    conn.commit()
    print(f"Inserted {len(df)} ingredients")

def create_indexes_and_optimize(conn):
    """Create additional indexes and optimize database."""
    print("Optimizing database...")
    
    # Analyze tables for query optimization
    conn.execute("ANALYZE")
    
    # Vacuum to reclaim space
    conn.execute("VACUUM")
    
    conn.commit()

def verify_database(conn):
    """Verify database integrity and content."""
    print("Verifying database...")
    
    cursor = conn.cursor()
    
    # Count records
    cursor.execute("SELECT COUNT(*) FROM ingredients")
    ingredient_count = cursor.fetchone()[0]
    print(f"Ingredients: {ingredient_count}")
    
    cursor.execute("SELECT COUNT(*) FROM functions")
    function_count = cursor.fetchone()[0]
    print(f"Functions: {function_count}")
    
    cursor.execute("SELECT COUNT(*) FROM ingredient_functions")
    ingredient_function_count = cursor.fetchone()[0]
    print(f"Ingredient-Function relationships: {ingredient_function_count}")
    
    cursor.execute("SELECT COUNT(*) FROM cas_numbers")
    cas_count = cursor.fetchone()[0]
    print(f"CAS numbers: {cas_count}")
    
    cursor.execute("SELECT COUNT(*) FROM ec_numbers")
    ec_count = cursor.fetchone()[0]
    print(f"EC numbers: {ec_count}")
    
    # Test a sample query
    cursor.execute("""
        SELECT i.inci_name, GROUP_CONCAT(f.function_name, ', ') as functions
        FROM ingredients i
        LEFT JOIN ingredient_functions if ON i.cosing_ref_no = if.ingredient_ref
        LEFT JOIN functions f ON if.function_id = f.id
        WHERE i.inci_name LIKE '%HYALURONIC%'
        GROUP BY i.cosing_ref_no
        LIMIT 5
    """)
    
    results = cursor.fetchall()
    print(f"\nSample query results (Hyaluronic acid compounds): {len(results)} found")
    for result in results:
        print(f"  {result[0]}: {result[1]}")

def main():
    """Main conversion function."""
    # Set up paths
    base_dir = Path(__file__).parent
    repo_dir = base_dir.parent
    ref_dir = repo_dir / 'ref'
    
    tsv_path = ref_dir / 'cosing.tsv'
    schema_path = base_dir / 'schema.sql'
    db_path = base_dir / 'cosing_ingredients.db'
    
    print("COSING Database Converter")
    print("=" * 40)
    
    # Verify input files exist
    if not tsv_path.exists():
        print(f"Error: TSV file not found: {tsv_path}")
        sys.exit(1)
    
    if not schema_path.exists():
        print(f"Error: Schema file not found: {schema_path}")
        sys.exit(1)
    
    try:
        # Create database
        conn = create_database(db_path, schema_path)
        
        # Load source data
        df = load_cosing_data(tsv_path)
        
        # Populate tables
        populate_functions(conn, df)
        populate_restrictions(conn, df)
        populate_ingredients(conn, df)
        
        # Optimize and verify
        create_indexes_and_optimize(conn)
        verify_database(conn)
        
        conn.close()
        
        print(f"\nDatabase created successfully: {db_path}")
        print(f"Database size: {os.path.getsize(db_path) / 1024 / 1024:.2f} MB")
        
    except Exception as e:
        print(f"Error: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()