-- COSING Cosmetic Ingredients Database Schema
-- Optimized for SkinTwin project integration and rapid querying
-- Based on COSING (COSmetic INGredient) database v2x

-- Main ingredients table
CREATE TABLE ingredients (
    cosing_ref_no INTEGER PRIMARY KEY,
    inci_name TEXT NOT NULL,
    inn_name TEXT,
    ph_eur_name TEXT,
    cas_no TEXT,
    ec_no TEXT,
    chemical_description TEXT,
    restriction TEXT,
    update_date DATE NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Functions lookup table (normalized from comma-separated values)
CREATE TABLE functions (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    function_name TEXT UNIQUE NOT NULL,
    description TEXT
);

-- Many-to-many relationship between ingredients and functions
CREATE TABLE ingredient_functions (
    ingredient_ref INTEGER NOT NULL,
    function_id INTEGER NOT NULL,
    PRIMARY KEY (ingredient_ref, function_id),
    FOREIGN KEY (ingredient_ref) REFERENCES ingredients(cosing_ref_no) ON DELETE CASCADE,
    FOREIGN KEY (function_id) REFERENCES functions(id) ON DELETE CASCADE
);

-- Restrictions lookup table for normalization
CREATE TABLE restrictions (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    restriction_code TEXT UNIQUE NOT NULL,
    description TEXT
);

-- CAS numbers table (some ingredients have multiple CAS numbers)
CREATE TABLE cas_numbers (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    ingredient_ref INTEGER NOT NULL,
    cas_number TEXT NOT NULL,
    is_primary BOOLEAN DEFAULT TRUE,
    FOREIGN KEY (ingredient_ref) REFERENCES ingredients(cosing_ref_no) ON DELETE CASCADE
);

-- EC numbers table (some ingredients have multiple EC numbers)
CREATE TABLE ec_numbers (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    ingredient_ref INTEGER NOT NULL,
    ec_number TEXT NOT NULL,
    is_primary BOOLEAN DEFAULT TRUE,
    FOREIGN KEY (ingredient_ref) REFERENCES ingredients(cosing_ref_no) ON DELETE CASCADE
);

-- Indexes for performance optimization
CREATE INDEX idx_ingredients_inci_name ON ingredients(inci_name);
CREATE INDEX idx_ingredients_cas_no ON ingredients(cas_no);
CREATE INDEX idx_ingredients_ec_no ON ingredients(ec_no);
CREATE INDEX idx_ingredients_update_date ON ingredients(update_date);
CREATE INDEX idx_functions_name ON functions(function_name);
CREATE INDEX idx_cas_numbers_cas ON cas_numbers(cas_number);
CREATE INDEX idx_ec_numbers_ec ON ec_numbers(ec_number);

-- Full-text search index for ingredient names and descriptions
CREATE VIRTUAL TABLE ingredients_fts USING fts5(
    cosing_ref_no,
    inci_name,
    chemical_description,
    content='ingredients',
    content_rowid='cosing_ref_no'
);

-- Triggers to maintain FTS index
CREATE TRIGGER ingredients_fts_insert AFTER INSERT ON ingredients
BEGIN
    INSERT INTO ingredients_fts(cosing_ref_no, inci_name, chemical_description)
    VALUES (new.cosing_ref_no, new.inci_name, new.chemical_description);
END;

CREATE TRIGGER ingredients_fts_delete AFTER DELETE ON ingredients
BEGIN
    DELETE FROM ingredients_fts WHERE cosing_ref_no = old.cosing_ref_no;
END;

CREATE TRIGGER ingredients_fts_update AFTER UPDATE ON ingredients
BEGIN
    DELETE FROM ingredients_fts WHERE cosing_ref_no = old.cosing_ref_no;
    INSERT INTO ingredients_fts(cosing_ref_no, inci_name, chemical_description)
    VALUES (new.cosing_ref_no, new.inci_name, new.chemical_description);
END;

-- Views for common queries
CREATE VIEW ingredient_summary AS
SELECT 
    i.cosing_ref_no,
    i.inci_name,
    i.cas_no,
    i.ec_no,
    GROUP_CONCAT(f.function_name, ', ') as functions,
    i.restriction,
    i.update_date
FROM ingredients i
LEFT JOIN ingredient_functions if ON i.cosing_ref_no = if.ingredient_ref
LEFT JOIN functions f ON if.function_id = f.id
GROUP BY i.cosing_ref_no;

-- View for SkinTwin integration (following .sk.inci naming pattern)
CREATE VIEW sk_inci_data AS
SELECT 
    i.cosing_ref_no as ref_no,
    i.inci_name,
    i.chemical_description,
    GROUP_CONCAT(f.function_name, '|') as functions,
    i.cas_no,
    i.ec_no,
    i.restriction,
    CASE 
        WHEN f.function_name LIKE '%SKIN%' THEN 'skincare'
        WHEN f.function_name LIKE '%HAIR%' THEN 'haircare'
        ELSE 'general'
    END as application_category
FROM ingredients i
LEFT JOIN ingredient_functions if ON i.cosing_ref_no = if.ingredient_ref
LEFT JOIN functions f ON if.function_id = f.id
GROUP BY i.cosing_ref_no;