#ifndef _SKIN_COGNITIVE_FRAMEWORK_HPP_
#define _SKIN_COGNITIVE_FRAMEWORK_HPP_

#include <vector>
#include <map>
#include <set>
#include <string>
#include <memory>
#include <functional>
#include <cmath>
#include "atomspace_integration.hpp"
#include "pln_integration.hpp"
#include "relevance_realization.hpp"

namespace plingua { namespace skin {

// Forward declarations
class SkinAccount;
class SkinTransaction;
class SkinLedger;

// Skin-specific accounting types adapted from GnuCash framework
enum class SkinAccountType {
    // Resource accounts (like Assets)
    NUTRIENT_POOL,      // Nutrients, vitamins, minerals in skin layers
    CELL_POPULATION,    // Different cell types (keratinocytes, melanocytes, etc.)
    PROTEIN_RESERVES,   // Collagen, elastin, structural proteins
    MOISTURE_BALANCE,   // Hydration levels across skin layers
    
    // Process accounts (like Liabilities)  
    METABOLIC_DEBT,     // Oxidative stress, accumulated damage
    INFLAMMATORY_LOAD,  // Inflammatory signaling burden
    REPAIR_OBLIGATION,  // Ongoing repair processes needing resources
    
    // Activity accounts (like Income/Expenses)
    CELLULAR_SYNTHESIS, // Protein synthesis, cell division
    DEGRADATION_LOSS,   // Protein breakdown, cell death
    ENVIRONMENTAL_IMPACT, // UV damage, pollution effects
    TREATMENT_INPUT     // Applied skincare treatments
};

// Biological transaction types for skin resource flow
enum class SkinTransactionType {
    NUTRIENT_TRANSFER,   // Movement of nutrients between layers
    SIGNALING_CASCADE,   // Growth factors, cytokines, hormones
    PROTEIN_SYNTHESIS,   // Collagen/elastin production
    CELLULAR_RENEWAL,    // Cell division and differentiation
    DAMAGE_REPAIR,       // DNA repair, antioxidant activity
    BARRIER_FUNCTION,    // Lipid barrier maintenance
    IMMUNE_RESPONSE      // Inflammatory or healing responses
};

// Skin-specific AtomSpace node types
enum class SkinAtomType {
    SKIN_LAYER_NODE,     // Epidermis, dermis, hypodermis
    CELL_TYPE_NODE,      // Keratinocyte, melanocyte, fibroblast
    MOLECULE_NODE,       // Collagen, elastin, hyaluronic acid
    PATHWAY_NODE,        // Metabolic pathways, signaling cascades
    CONDITION_NODE,      // Acne, aging, pigmentation
    TREATMENT_NODE       // Retinoids, peptides, antioxidants
};

// Truth values for biological confidence
struct SkinTruthValue {
    double biological_strength;  // How well-established the biological relationship is
    double clinical_confidence;  // Evidence from clinical studies
    double individual_relevance; // Personalized relevance for this skin profile
    
    SkinTruthValue(double bio_str = 0.5, double clin_conf = 0.5, double indiv_rel = 0.5)
        : biological_strength(bio_str), clinical_confidence(clin_conf), individual_relevance(indiv_rel) {}
        
    // Convert to PLN truth value for reasoning
    pln::PLNTruthValue toPLN() const {
        double combined_strength = (biological_strength + individual_relevance) / 2.0;
        return pln::PLNTruthValue(combined_strength, clinical_confidence);
    }
};

// Skin account representing biological resource pools or processes
class SkinAccount {
public:
    unsigned id;
    std::string name;
    SkinAccountType account_type;
    SkinAtomType atom_type;
    
    // Biological properties
    double current_balance;      // Current resource level or activity rate
    double baseline_level;       // Normal/healthy baseline
    double capacity_limit;       // Maximum sustainable level
    double depletion_rate;       // Natural consumption/decay rate
    double regeneration_rate;    // Natural replenishment rate
    
    // Cognitive properties from ECAN
    double short_term_importance;  // STI - immediate biological priority
    double long_term_importance;   // LTI - sustained health significance
    double attention_wage;         // Resources allocated per cycle
    double attention_rent;         // Maintenance cost per cycle
    
    // Truth value for account reliability
    SkinTruthValue truth_value;
    
    // Hierarchical relationships
    std::vector<unsigned> child_accounts;  // Sub-components
    unsigned parent_account;               // Parent system
    
    SkinAccount(unsigned account_id, const std::string& account_name, 
                SkinAccountType type, SkinAtomType atom_type_val)
        : id(account_id), name(account_name), account_type(type), atom_type(atom_type_val),
          current_balance(0.0), baseline_level(100.0), capacity_limit(200.0),
          depletion_rate(0.01), regeneration_rate(0.02),
          short_term_importance(50.0), long_term_importance(100.0),
          attention_wage(1.0), attention_rent(0.1),
          parent_account(0) {}
    
    // Calculate biological health score (0.0 to 1.0)
    double computeHealthScore() const {
        if (capacity_limit <= 0) return 0.0;
        double balance_ratio = current_balance / capacity_limit;
        double baseline_ratio = current_balance / baseline_level;
        return std::min(1.0, (balance_ratio + baseline_ratio) / 2.0);
    }
    
    // Update biological dynamics
    void updateBiologicalState(double dt) {
        // Natural regeneration and depletion
        current_balance += regeneration_rate * dt;
        current_balance -= depletion_rate * dt;
        
        // Enforce capacity limits
        current_balance = std::max(0.0, std::min(capacity_limit, current_balance));
        
        // Update truth value based on stability
        double stability = 1.0 - std::abs(current_balance - baseline_level) / baseline_level;
        truth_value.biological_strength = 0.8 * truth_value.biological_strength + 0.2 * stability;
    }
};

// Biological transaction representing resource flow or biological process
class SkinTransaction {
public:
    unsigned id;
    std::string description;
    SkinTransactionType transaction_type;
    
    // Source and destination accounts (double-entry for biological processes)
    unsigned from_account_id;  // Resource source
    unsigned to_account_id;    // Resource destination
    double amount;             // Amount transferred
    
    // Biological context
    double efficiency;         // Process efficiency (0.0 to 1.0)
    double energy_cost;        // ATP or metabolic cost
    std::vector<unsigned> cofactor_requirements; // Required enzymes, vitamins, etc.
    std::vector<unsigned> regulatory_factors;    // Hormones, growth factors affecting process
    
    // Truth value for transaction validity
    SkinTruthValue truth_value;
    
    // Temporal properties
    double start_time;
    double duration;
    bool is_completed;
    
    SkinTransaction(unsigned txn_id, const std::string& desc, SkinTransactionType type,
                   unsigned from_id, unsigned to_id, double transfer_amount)
        : id(txn_id), description(desc), transaction_type(type),
          from_account_id(from_id), to_account_id(to_id), amount(transfer_amount),
          efficiency(1.0), energy_cost(0.0),
          start_time(0.0), duration(1.0), is_completed(false) {}
    
    // Validate biological feasibility using PLN
    bool validateBiologicalFeasibility() const {
        // Check if source has sufficient resources
        // Check if cofactors are available
        // Check if regulatory conditions are met
        double feasibility_score = efficiency * truth_value.biological_strength;
        return feasibility_score > 0.5;  // Threshold for biological viability
    }
};

// Skin ledger managing all biological accounting
class SkinLedger {
public:
    std::map<unsigned, std::shared_ptr<SkinAccount>> accounts;
    std::map<unsigned, std::shared_ptr<SkinTransaction>> transactions;
    unsigned next_account_id;
    unsigned next_transaction_id;
    
    // Integration with cognitive framework
    plingua::atomspace::AtomSpace* atom_space;
    plingua::pln::PLNInferenceEngine* pln_engine;
    plingua::rr::RRHypergraph* rr_hypergraph;
    
    SkinLedger() : next_account_id(1), next_transaction_id(1),
                   atom_space(nullptr), pln_engine(nullptr), rr_hypergraph(nullptr) {}
    
    // Account management
    unsigned createAccount(const std::string& name, SkinAccountType type, SkinAtomType atom_type) {
        auto account = std::make_shared<SkinAccount>(next_account_id++, name, type, atom_type);
        accounts[account->id] = account;
        
        // Create corresponding AtomSpace representation if available
        if (atom_space) {
            std::string atom_name = name + "_" + std::to_string(account->id);
            atom_space->addConceptNode(atom_name, account->truth_value.biological_strength, 
                                     account->truth_value.clinical_confidence);
        }
        
        return account->id;
    }
    
    // Transaction processing with biological validation
    bool processTransaction(const SkinTransaction& transaction) {
        if (!transaction.validateBiologicalFeasibility()) {
            return false; // Biologically infeasible
        }
        
        auto from_account = accounts.find(transaction.from_account_id);
        auto to_account = accounts.find(transaction.to_account_id);
        
        if (from_account == accounts.end() || to_account == accounts.end()) {
            return false; // Invalid accounts
        }
        
        // Check resource availability (allow zero balance for special accounts like treatments)
        if (from_account->second->current_balance < transaction.amount && 
            from_account->second->account_type != SkinAccountType::TREATMENT_INPUT) {
            return false; // Insufficient resources
        }
        
        // Execute double-entry biological transfer
        from_account->second->current_balance -= transaction.amount;
        to_account->second->current_balance += transaction.amount * transaction.efficiency;
        
        // Ensure non-negative balances
        from_account->second->current_balance = std::max(0.0, from_account->second->current_balance);
        
        // Store transaction
        auto txn = std::make_shared<SkinTransaction>(transaction);
        txn->id = next_transaction_id++;
        txn->is_completed = true;
        transactions[txn->id] = txn;
        
        return true;
    }
    
    // Generate trial balance for biological system
    std::map<SkinAccountType, double> generateTrialBalance() const {
        std::map<SkinAccountType, double> balance_by_type;
        
        for (const auto& account_pair : accounts) {
            auto account = account_pair.second;
            balance_by_type[account->account_type] += account->current_balance;
        }
        
        return balance_by_type;
    }
    
    // PLN-based biological reasoning
    std::vector<std::string> generateBiologicalInsights() const {
        std::vector<std::string> insights;
        
        if (!pln_engine) return insights;
        
        // Analyze resource imbalances
        auto trial_balance = generateTrialBalance();
        
        for (const auto& balance_pair : trial_balance) {
            if (balance_pair.second < 50.0) { // Low resource threshold
                insights.push_back("Low " + std::to_string(static_cast<int>(balance_pair.first)) + 
                                 " resources detected - consider intervention");
            }
        }
        
        return insights;
    }
    
    // ECAN attention allocation for biological priorities
    void updateAttentionAllocation() {
        double total_sti_fund = 1000.0;  // Total attention budget
        double total_priority = 0.0;
        
        // Calculate total priority across all accounts
        for (const auto& account_pair : accounts) {
            total_priority += account_pair.second->short_term_importance;
        }
        
        // Allocate attention based on biological priority
        for (auto& account_pair : accounts) {
            auto account = account_pair.second;
            if (total_priority > 0) {
                double priority_ratio = account->short_term_importance / total_priority;
                double allocated_attention = total_sti_fund * priority_ratio;
                
                // Pay attention wage and collect rent
                account->current_balance += account->attention_wage * allocated_attention / 100.0;
                account->current_balance -= account->attention_rent;
            }
            
            // Update biological state
            account->updateBiologicalState(0.1);
        }
    }
    
    // MOSES optimization for treatment strategies
    std::vector<unsigned> optimizeTreatmentStrategy(unsigned condition_account_id) {
        std::vector<unsigned> treatment_recommendations;
        
        auto condition_account = accounts.find(condition_account_id);
        if (condition_account == accounts.end()) {
            return treatment_recommendations;
        }
        
        // Simple optimization: recommend treatments that address low resources
        for (const auto& account_pair : accounts) {
            auto account = account_pair.second;
            if (account->account_type == SkinAccountType::TREATMENT_INPUT &&
                account->current_balance > condition_account->second->current_balance) {
                treatment_recommendations.push_back(account->id);
            }
        }
        
        return treatment_recommendations;
    }
};

// Initialize skin cognitive accounting framework
class SkinCognitiveFramework {
public:
    SkinLedger ledger;
    plingua::atomspace::AtomSpace atom_space;
    plingua::pln::PLNInferenceEngine pln_engine;
    plingua::rr::RRHypergraph rr_hypergraph;
    
    SkinCognitiveFramework() : pln_engine(&atom_space) {
        // Connect components
        ledger.atom_space = &atom_space;
        ledger.pln_engine = &pln_engine;
        ledger.rr_hypergraph = &rr_hypergraph;
        
        // Initialize with basic skin architecture
        initializeBasicSkinArchitecture();
    }
    
    void initializeBasicSkinArchitecture() {
        // Create skin layer accounts
        unsigned epidermis = ledger.createAccount("Epidermis", SkinAccountType::CELL_POPULATION, 
                                                 SkinAtomType::SKIN_LAYER_NODE);
        unsigned dermis = ledger.createAccount("Dermis", SkinAccountType::CELL_POPULATION, 
                                             SkinAtomType::SKIN_LAYER_NODE);
        unsigned hypodermis = ledger.createAccount("Hypodermis", SkinAccountType::CELL_POPULATION, 
                                                  SkinAtomType::SKIN_LAYER_NODE);
        
        // Create nutrient pools
        unsigned vitamin_c = ledger.createAccount("Vitamin C Pool", SkinAccountType::NUTRIENT_POOL,
                                                 SkinAtomType::MOLECULE_NODE);
        unsigned collagen = ledger.createAccount("Collagen Reserves", SkinAccountType::PROTEIN_RESERVES,
                                               SkinAtomType::MOLECULE_NODE);
        
        // Set initial balances representing healthy skin
        ledger.accounts[epidermis]->current_balance = 100.0;
        ledger.accounts[dermis]->current_balance = 100.0;
        ledger.accounts[hypodermis]->current_balance = 100.0;
        ledger.accounts[vitamin_c]->current_balance = 75.0;
        ledger.accounts[collagen]->current_balance = 90.0;
    }
    
    // Main cognitive processing cycle
    void processCognitiveCycle() {
        // 1. Update biological states
        ledger.updateAttentionAllocation();
        
        // 2. Run PLN inference for biological insights
        auto insights = ledger.generateBiologicalInsights();
        
        // 3. Update RR dynamics based on biological priorities
        for (const auto& account_pair : ledger.accounts) {
            auto account = account_pair.second;
            
            // Map account to RR node if it doesn't exist
            if (rr_hypergraph.nodes.find(account->id) == rr_hypergraph.nodes.end()) {
                unsigned rr_node = rr_hypergraph.addMembraneNode(account->id, account->name, 
                                                               plingua::rr::AARType::AGENT);
                auto rr_node_ptr = rr_hypergraph.nodes[rr_node];
                if (rr_node_ptr) {
                    rr_node_ptr->salience = account->short_term_importance / 100.0;
                    rr_node_ptr->affordance_realization = account->computeHealthScore();
                }
            }
        }
        
        // 4. Update RR hypergraph
        rr_hypergraph.updateRelevanceRealization(0.1);
    }
};

}} // namespace plingua::skin

#endif // _SKIN_COGNITIVE_FRAMEWORK_HPP_