# COSING Cosmetic Ingredients Database

## Overview

This directory contains the optimized database structure for the COSING (COSmetic INGredient) database, specifically designed for integration with the SkinTwin project. The database normalizes and structures cosmetic ingredient data for efficient querying and analysis.

## Source Data

The database is built from two identical source files:
- `ref/COSING_Ingredients-Fragrance Inventory_v2x.xlsx` - Excel format (7.9MB)
- `ref/cosing.tsv` - Tab-separated values format (6.2MB)

Both files contain 30,070 cosmetic ingredient records with identical data.

## Database Structure

### Core Tables

1. **ingredients** - Main ingredient data
   - `cosing_ref_no` (PRIMARY KEY) - COSING reference number
   - `inci_name` - International Nomenclature of Cosmetic Ingredients name
   - `inn_name` - International Nonproprietary Name
   - `ph_eur_name` - European Pharmacopoeia name
   - `cas_no` - Chemical Abstracts Service registry number
   - `ec_no` - European Community number
   - `chemical_description` - Chemical/IUPAC name and description
   - `restriction` - Regulatory restrictions
   - `update_date` - Last update date

2. **functions** - Normalized function lookup table
   - 81 unique cosmetic functions (e.g., "SKIN CONDITIONING", "SURFACTANT - CLEANSING")

3. **ingredient_functions** - Many-to-many relationship table
   - Links ingredients to their functions
   - 53,238 total function assignments

4. **cas_numbers** - Normalized CAS number storage
   - Handles multiple CAS numbers per ingredient
   - 15,505 total CAS numbers

5. **ec_numbers** - Normalized EC number storage
   - 10,091 total EC numbers

### Indexes and Optimization

- Full-text search index on ingredient names and descriptions
- Optimized indexes on commonly queried fields
- Views for common query patterns
- SQLite database optimized for read performance

## Files

- `schema.sql` - Database schema definition
- `convert_cosing.py` - Data conversion script
- `query_cosing.py` - Query interface and API
- `cosing_ingredients.db` - SQLite database (11.4MB)
- `cosing_sk_inci.ini` - SkinTwin .sk.inci format export
- `README.md` - This documentation

## Usage

### Database Creation

```bash
# Create database from source data
python3 convert_cosing.py
```

### Querying

```bash
# Search ingredients
python3 query_cosing.py search "hyaluronic"

# Get ingredient details
python3 query_cosing.py ingredient 31367

# Find ingredients by function
python3 query_cosing.py function "SKIN CONDITIONING"

# Get all functions
python3 query_cosing.py functions

# Get skin conditioning ingredients
python3 query_cosing.py skin

# Database statistics
python3 query_cosing.py stats

# Export SkinTwin format
python3 query_cosing.py export output.ini
```

### Python API

```python
from query_cosing import COSINGDatabase

with COSINGDatabase() as db:
    # Search ingredients
    results = db.search_ingredients("hyaluronic")
    
    # Get ingredient details
    ingredient = db.get_ingredient_by_ref(31367)
    
    # Get skin conditioning ingredients
    skin_ingredients = db.get_skin_conditioning_ingredients()
    
    # Get database statistics
    stats = db.get_ingredient_stats()
```

## Integration with SkinTwin

The database is designed for seamless integration with the SkinTwin project architecture:

### .sk.inci Format Support

The database exports data in SkinTwin's hierarchical file format:
- `.sk.inci` files for individual ingredients
- Categories: skincare, haircare, general
- Compatible with SkinTwin's rapid querying system

### Performance Optimizations

- Full-text search for rapid ingredient discovery
- Indexed queries for function-based searches
- Normalized structure for data integrity
- View-based abstractions for common queries

### Application Categories

Ingredients are automatically categorized:
- **skincare** - Contains skin-related functions
- **haircare** - Contains hair-related functions  
- **general** - Other cosmetic applications

## Database Statistics

- **Total Ingredients**: 30,070
- **Total Functions**: 81
- **Function Assignments**: 53,238
- **CAS Numbers**: 15,505
- **EC Numbers**: 10,091
- **Database Size**: 11.4MB

### Top Functions by Usage

1. SKIN CONDITIONING (13,066 ingredients)
2. SKIN CONDITIONING - EMOLLIENT (3,341 ingredients)
3. HAIR CONDITIONING (3,328 ingredients)
4. SURFACTANT - CLEANSING (3,076 ingredients)
5. SURFACTANT - EMULSIFYING (2,750 ingredients)
6. PERFUMING (2,711 ingredients)
7. ANTIOXIDANT (2,558 ingredients)
8. SKIN PROTECTING (2,350 ingredients)
9. HUMECTANT (2,090 ingredients)
10. FRAGRANCE (1,404 ingredients)

## Example Queries

### Find Hyaluronic Acid Compounds
```sql
SELECT i.inci_name, GROUP_CONCAT(f.function_name, ', ') as functions
FROM ingredients i
LEFT JOIN ingredient_functions if ON i.cosing_ref_no = if.ingredient_ref
LEFT JOIN functions f ON if.function_id = f.id
WHERE i.inci_name LIKE '%HYALURONIC%'
GROUP BY i.cosing_ref_no;
```

### Skin Conditioning Ingredients
```sql
SELECT i.inci_name, i.chemical_description
FROM ingredients i
JOIN ingredient_functions if ON i.cosing_ref_no = if.ingredient_ref
JOIN functions f ON if.function_id = f.id
WHERE f.function_name = 'SKIN CONDITIONING'
ORDER BY i.inci_name;
```

### Search by CAS Number
```sql
SELECT i.inci_name, cn.cas_number
FROM ingredients i
JOIN cas_numbers cn ON i.cosing_ref_no = cn.ingredient_ref
WHERE cn.cas_number = '58-61-7';
```

## Data Quality Notes

- 98.3% of ingredients have no INN name (specialized cosmetic ingredients)
- 99.4% have no Ph. Eur. name (non-pharmaceutical)
- 38.6% have CAS numbers
- 49.7% have EC numbers
- 44.6% have multiple functions
- All ingredients have INCI names and update dates

## SkinTwin Integration Benefits

1. **Rapid Querying**: Optimized for the fast ingredient lookups described in SkinTwin.txt
2. **Hierarchical Organization**: Supports .sk.inci file structure
3. **Function-Based Analysis**: Enables rapid analysis by cosmetic function
4. **Chemical Identification**: CAS/EC number lookup for precise ingredient identification
5. **Category Classification**: Automatic skincare vs. other application categorization
6. **Full-Text Search**: Enables natural language ingredient discovery
7. **Data Integrity**: Normalized structure prevents data inconsistencies
8. **Performance**: 11.4MB database for 30K+ ingredients with sub-second queries

This optimized database structure provides the foundation for efficient cosmetic ingredient analysis within the SkinTwin ecosystem.