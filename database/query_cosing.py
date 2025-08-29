#!/usr/bin/env python3
"""
COSING Database Query Interface
Provides easy querying capabilities for the COSING cosmetic ingredients database.
Designed for SkinTwin project integration.
"""

import sqlite3
import sys
import json
from pathlib import Path

class COSINGDatabase:
    """Interface for querying the COSING cosmetic ingredients database."""
    
    def __init__(self, db_path=None):
        if db_path is None:
            db_path = Path(__file__).parent / 'cosing_ingredients.db'
        
        self.db_path = db_path
        self.conn = sqlite3.connect(db_path)
        self.conn.row_factory = sqlite3.Row  # Enable column access by name
    
    def __enter__(self):
        return self
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        self.conn.close()
    
    def search_ingredients(self, search_term, limit=10):
        """Search ingredients by name or description using full-text search."""
        cursor = self.conn.cursor()
        
        query = """
        SELECT i.cosing_ref_no, i.inci_name, i.chemical_description,
               GROUP_CONCAT(f.function_name, ', ') as functions
        FROM ingredients_fts fts
        JOIN ingredients i ON fts.cosing_ref_no = i.cosing_ref_no
        LEFT JOIN ingredient_functions if ON i.cosing_ref_no = if.ingredient_ref
        LEFT JOIN functions f ON if.function_id = f.id
        WHERE ingredients_fts MATCH ?
        GROUP BY i.cosing_ref_no
        LIMIT ?
        """
        
        cursor.execute(query, (search_term, limit))
        return [dict(row) for row in cursor.fetchall()]
    
    def get_ingredient_by_ref(self, cosing_ref_no):
        """Get detailed information about a specific ingredient by COSING reference number."""
        cursor = self.conn.cursor()
        
        # Get basic ingredient info
        cursor.execute("""
            SELECT * FROM ingredients WHERE cosing_ref_no = ?
        """, (cosing_ref_no,))
        
        ingredient = cursor.fetchone()
        if not ingredient:
            return None
        
        ingredient = dict(ingredient)
        
        # Get functions
        cursor.execute("""
            SELECT f.function_name 
            FROM ingredient_functions if
            JOIN functions f ON if.function_id = f.id
            WHERE if.ingredient_ref = ?
        """, (cosing_ref_no,))
        
        ingredient['functions'] = [row[0] for row in cursor.fetchall()]
        
        # Get CAS numbers
        cursor.execute("""
            SELECT cas_number, is_primary 
            FROM cas_numbers 
            WHERE ingredient_ref = ?
            ORDER BY is_primary DESC
        """, (cosing_ref_no,))
        
        ingredient['cas_numbers'] = [row[0] for row in cursor.fetchall()]
        
        # Get EC numbers
        cursor.execute("""
            SELECT ec_number, is_primary 
            FROM ec_numbers 
            WHERE ingredient_ref = ?
            ORDER BY is_primary DESC
        """, (cosing_ref_no,))
        
        ingredient['ec_numbers'] = [row[0] for row in cursor.fetchall()]
        
        return ingredient
    
    def get_ingredients_by_function(self, function_name, limit=50):
        """Get ingredients that have a specific function."""
        cursor = self.conn.cursor()
        
        query = """
        SELECT i.cosing_ref_no, i.inci_name, i.chemical_description
        FROM ingredients i
        JOIN ingredient_functions if ON i.cosing_ref_no = if.ingredient_ref
        JOIN functions f ON if.function_id = f.id
        WHERE f.function_name LIKE ?
        ORDER BY i.inci_name
        LIMIT ?
        """
        
        cursor.execute(query, (f'%{function_name}%', limit))
        return [dict(row) for row in cursor.fetchall()]
    
    def get_all_functions(self):
        """Get all available functions."""
        cursor = self.conn.cursor()
        cursor.execute("SELECT function_name FROM functions ORDER BY function_name")
        return [row[0] for row in cursor.fetchall()]
    
    def get_skin_conditioning_ingredients(self, limit=100):
        """Get ingredients with skin conditioning functions (SkinTwin focus)."""
        return self.get_ingredients_by_function('SKIN CONDITIONING', limit)
    
    def search_by_cas(self, cas_number):
        """Search ingredients by CAS number."""
        cursor = self.conn.cursor()
        
        query = """
        SELECT i.cosing_ref_no, i.inci_name, cn.cas_number
        FROM ingredients i
        JOIN cas_numbers cn ON i.cosing_ref_no = cn.ingredient_ref
        WHERE cn.cas_number = ?
        """
        
        cursor.execute(query, (cas_number,))
        return [dict(row) for row in cursor.fetchall()]
    
    def get_ingredient_stats(self):
        """Get database statistics."""
        cursor = self.conn.cursor()
        
        stats = {}
        
        cursor.execute("SELECT COUNT(*) FROM ingredients")
        stats['total_ingredients'] = cursor.fetchone()[0]
        
        cursor.execute("SELECT COUNT(*) FROM functions")
        stats['total_functions'] = cursor.fetchone()[0]
        
        cursor.execute("SELECT COUNT(*) FROM ingredient_functions")
        stats['total_function_assignments'] = cursor.fetchone()[0]
        
        cursor.execute("SELECT COUNT(*) FROM cas_numbers")
        stats['total_cas_numbers'] = cursor.fetchone()[0]
        
        cursor.execute("SELECT COUNT(*) FROM ec_numbers")
        stats['total_ec_numbers'] = cursor.fetchone()[0]
        
        # Top functions
        cursor.execute("""
            SELECT f.function_name, COUNT(*) as count
            FROM ingredient_functions if
            JOIN functions f ON if.function_id = f.id
            GROUP BY f.function_name
            ORDER BY count DESC
            LIMIT 10
        """)
        
        stats['top_functions'] = [{'function': row[0], 'count': row[1]} 
                                 for row in cursor.fetchall()]
        
        return stats
    
    def export_sk_inci_format(self, output_file):
        """Export data in SkinTwin .sk.inci format for integration."""
        cursor = self.conn.cursor()
        
        query = """
        SELECT 
            i.cosing_ref_no,
            i.inci_name,
            i.chemical_description,
            GROUP_CONCAT(f.function_name, '|') as functions,
            i.cas_no,
            i.ec_no,
            i.restriction,
            CASE 
                WHEN GROUP_CONCAT(f.function_name) LIKE '%SKIN%' THEN 'skincare'
                WHEN GROUP_CONCAT(f.function_name) LIKE '%HAIR%' THEN 'haircare'
                ELSE 'general'
            END as category
        FROM ingredients i
        LEFT JOIN ingredient_functions if ON i.cosing_ref_no = if.ingredient_ref
        LEFT JOIN functions f ON if.function_id = f.id
        GROUP BY i.cosing_ref_no
        ORDER BY i.inci_name
        """
        
        cursor.execute(query)
        
        with open(output_file, 'w') as f:
            f.write("# SkinTwin INCI Database Export\n")
            f.write("# Format: .sk.inci compatible\n")
            f.write("# Generated from COSING database\n\n")
            
            for row in cursor.fetchall():
                data = dict(row)
                f.write(f"[{data['cosing_ref_no']}]\n")
                f.write(f"inci_name = {data['inci_name']}\n")
                if data['chemical_description']:
                    f.write(f"description = {data['chemical_description']}\n")
                if data['functions']:
                    f.write(f"functions = {data['functions']}\n")
                if data['cas_no']:
                    f.write(f"cas_no = {data['cas_no']}\n")
                if data['ec_no']:
                    f.write(f"ec_no = {data['ec_no']}\n")
                f.write(f"category = {data['category']}\n")
                if data['restriction']:
                    f.write(f"restriction = {data['restriction']}\n")
                f.write("\n")

def main():
    """Command-line interface for database queries."""
    if len(sys.argv) < 2:
        print("COSING Database Query Interface")
        print("Usage:")
        print("  python3 query_cosing.py search <term>")
        print("  python3 query_cosing.py ingredient <cosing_ref_no>")
        print("  python3 query_cosing.py function <function_name>")
        print("  python3 query_cosing.py functions")
        print("  python3 query_cosing.py skin")
        print("  python3 query_cosing.py stats")
        print("  python3 query_cosing.py export <output_file>")
        sys.exit(1)
    
    command = sys.argv[1]
    
    with COSINGDatabase() as db:
        if command == 'search' and len(sys.argv) > 2:
            results = db.search_ingredients(sys.argv[2])
            for result in results:
                print(f"{result['cosing_ref_no']}: {result['inci_name']}")
                print(f"  Functions: {result['functions']}")
                print()
        
        elif command == 'ingredient' and len(sys.argv) > 2:
            ingredient = db.get_ingredient_by_ref(int(sys.argv[2]))
            if ingredient:
                print(json.dumps(ingredient, indent=2, default=str))
            else:
                print("Ingredient not found")
        
        elif command == 'function' and len(sys.argv) > 2:
            results = db.get_ingredients_by_function(sys.argv[2])
            for result in results:
                print(f"{result['cosing_ref_no']}: {result['inci_name']}")
        
        elif command == 'functions':
            functions = db.get_all_functions()
            for func in functions:
                print(func)
        
        elif command == 'skin':
            results = db.get_skin_conditioning_ingredients(20)
            print("Skin conditioning ingredients:")
            for result in results:
                print(f"  {result['inci_name']}")
        
        elif command == 'stats':
            stats = db.get_ingredient_stats()
            print(json.dumps(stats, indent=2))
        
        elif command == 'export' and len(sys.argv) > 2:
            db.export_sk_inci_format(sys.argv[2])
            print(f"Exported to {sys.argv[2]}")
        
        else:
            print("Invalid command or missing arguments")

if __name__ == "__main__":
    main()