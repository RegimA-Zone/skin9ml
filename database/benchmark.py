#!/usr/bin/env python3
"""
Database Performance Benchmark
Tests query performance for the COSING database.
"""

import time
import sqlite3
from pathlib import Path
from query_cosing import COSINGDatabase

def benchmark_queries():
    """Run performance benchmarks on common query patterns."""
    db_path = Path(__file__).parent / 'cosing_ingredients.db'
    
    print("COSING Database Performance Benchmark")
    print("=" * 40)
    
    with COSINGDatabase(db_path) as db:
        
        # Test 1: Simple ingredient lookup by ID
        start_time = time.time()
        ingredient = db.get_ingredient_by_ref(31367)
        elapsed = time.time() - start_time
        print(f"1. Ingredient lookup by ID: {elapsed*1000:.2f}ms")
        
        # Test 2: Search by INCI name pattern
        start_time = time.time()
        conn = db.conn
        cursor = conn.cursor()
        cursor.execute("SELECT * FROM ingredients WHERE inci_name LIKE '%HYALURONIC%'")
        results = cursor.fetchall()
        elapsed = time.time() - start_time
        print(f"2. Pattern search (LIKE): {elapsed*1000:.2f}ms ({len(results)} results)")
        
        # Test 3: Function-based search
        start_time = time.time()
        results = db.get_ingredients_by_function('SKIN CONDITIONING', 100)
        elapsed = time.time() - start_time
        print(f"3. Function search: {elapsed*1000:.2f}ms ({len(results)} results)")
        
        # Test 4: CAS number lookup
        start_time = time.time()
        results = db.search_by_cas('58-61-7')
        elapsed = time.time() - start_time
        print(f"4. CAS number lookup: {elapsed*1000:.2f}ms ({len(results)} results)")
        
        # Test 5: Complex join query
        start_time = time.time()
        cursor.execute("""
            SELECT i.inci_name, GROUP_CONCAT(f.function_name, ', ') as functions
            FROM ingredients i
            LEFT JOIN ingredient_functions if ON i.cosing_ref_no = if.ingredient_ref
            LEFT JOIN functions f ON if.function_id = f.id
            WHERE i.inci_name LIKE '%ACID%'
            GROUP BY i.cosing_ref_no
            LIMIT 50
        """)
        results = cursor.fetchall()
        elapsed = time.time() - start_time
        print(f"5. Complex join query: {elapsed*1000:.2f}ms ({len(results)} results)")
        
        # Test 6: Full-text search (if available)
        start_time = time.time()
        try:
            cursor.execute("""
                SELECT COUNT(*) FROM ingredients_fts WHERE ingredients_fts MATCH 'skin'
            """)
            count = cursor.fetchone()[0]
            elapsed = time.time() - start_time
            print(f"6. Full-text search: {elapsed*1000:.2f}ms ({count} matches)")
        except:
            print("6. Full-text search: Not available")
        
        # Test 7: Database statistics
        start_time = time.time()
        stats = db.get_ingredient_stats()
        elapsed = time.time() - start_time
        print(f"7. Statistics query: {elapsed*1000:.2f}ms")
        
        print("\nDatabase size:", f"{db_path.stat().st_size / 1024 / 1024:.2f} MB")
        print("Total ingredients:", stats['total_ingredients'])

if __name__ == "__main__":
    benchmark_queries()