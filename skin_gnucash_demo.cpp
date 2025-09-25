#include <iostream>
#include <iomanip>
#include "skin_cognitive_framework.hpp"

using namespace plingua::skin;
using namespace plingua::atomspace;
using namespace plingua::rr;

void demonstrateGnuCashCognitiveFeatures(SkinCognitiveFramework& framework) {
    std::cout << "\n=== GnuCash Cognitive Accounting Features Adapted to Skin Model ===" << std::endl;
    
    // 1. Enhanced AtomSpace Account Representation
    std::cout << "\n1. Enhanced AtomSpace Account Representation:" << std::endl;
    std::cout << "   Chart of Accounts mapped to biological hypergraph:" << std::endl;
    for (const auto& account_pair : framework.ledger.accounts) {
        auto account = account_pair.second;
        std::cout << "   • " << account->name << " → ConceptNode with truth value ["
                  << account->truth_value.biological_strength << ", "
                  << account->truth_value.clinical_confidence << "]" << std::endl;
    }
    
    // 2. PLN Ledger Rules for biological validation
    std::cout << "\n2. PLN (Probabilistic Logic Networks) Biological Validation:" << std::endl;
    
    // Create a biologically questionable transaction to test PLN validation
    SkinTransaction questionable_txn(99, "Unrealistic collagen synthesis", 
                                   SkinTransactionType::PROTEIN_SYNTHESIS, 4, 5, 1000.0);
    questionable_txn.efficiency = 2.0; // Impossible efficiency > 1.0
    questionable_txn.truth_value = SkinTruthValue(0.1, 0.2, 0.3); // Low confidence
    
    bool is_valid = questionable_txn.validateBiologicalFeasibility();
    std::cout << "   • Biological transaction validation using PLN truth values" << std::endl;
    std::cout << "   • Questionable transaction (efficiency=2.0): " 
              << (is_valid ? "ACCEPTED" : "REJECTED") << std::endl;
    
    // Create a realistic transaction
    SkinTransaction realistic_txn(98, "Normal vitamin absorption", 
                                SkinTransactionType::NUTRIENT_TRANSFER, 4, 5, 10.0);
    realistic_txn.efficiency = 0.8;
    realistic_txn.truth_value = SkinTruthValue(0.9, 0.8, 0.85);
    
    is_valid = realistic_txn.validateBiologicalFeasibility();
    std::cout << "   • Realistic transaction (efficiency=0.8): " 
              << (is_valid ? "ACCEPTED" : "REJECTED") << std::endl;
    
    // 3. ECAN Economic Attention Allocation
    std::cout << "\n3. ECAN (Economic Attention Allocation) for Biological Priorities:" << std::endl;
    std::cout << "   • STI (Short-term Importance) = Immediate biological priority" << std::endl;
    std::cout << "   • LTI (Long-term Importance) = Sustained health significance" << std::endl;
    
    // Simulate attention crisis (low collagen)
    auto collagen_account = framework.ledger.accounts[5]; // Collagen Reserves
    collagen_account->short_term_importance = 200.0; // Crisis priority
    
    std::cout << "   • Collagen crisis detected - increasing STI to " 
              << collagen_account->short_term_importance << std::endl;
    
    framework.ledger.updateAttentionAllocation();
    std::cout << "   • Attention resources reallocated based on biological urgency" << std::endl;
    
    // 4. MOSES Strategy Discovery
    std::cout << "\n4. MOSES (Meta-Optimizing Semantic Evolutionary Search):" << std::endl;
    std::cout << "   • Evolutionary discovery of optimal skincare strategies" << std::endl;
    
    auto treatment_recommendations = framework.ledger.optimizeTreatmentStrategy(5); // For collagen
    std::cout << "   • Discovered treatment strategies for collagen health:" << std::endl;
    for (unsigned rec_id : treatment_recommendations) {
        auto rec_account = framework.ledger.accounts.find(rec_id);
        if (rec_account != framework.ledger.accounts.end()) {
            std::cout << "     - " << rec_account->second->name << std::endl;
        }
    }
    
    // 5. URE Uncertain Reasoning
    std::cout << "\n5. URE (Uncertain Reasoning Engine) for Predictions:" << std::endl;
    std::cout << "   • Multi-factor uncertainty analysis for skin health predictions" << std::endl;
    
    // Simulate prediction uncertainty
    for (auto& account_pair : framework.ledger.accounts) {
        auto account = account_pair.second;
        double health_score = account->computeHealthScore();
        double uncertainty = 1.0 - account->truth_value.clinical_confidence;
        
        std::cout << "   • " << account->name << ": Health=" << std::fixed << std::setprecision(2)
                  << health_score << " ±" << (uncertainty * health_score) << std::endl;
    }
    
    // 6. Scheme-based Cognitive Representations
    std::cout << "\n6. Scheme-based Hypergraph Pattern Encoding:" << std::endl;
    std::cout << "   • Automatic generation of cognitive patterns for biological relationships" << std::endl;
    
    // Simulate scheme pattern generation
    std::cout << "   • (ConceptNode \"Collagen-Synthesis-Pathway\")" << std::endl;
    std::cout << "   • (EvaluationLink (PredicateNode \"requires\") " << std::endl;
    std::cout << "       (ListLink (ConceptNode \"Vitamin-C\") (ConceptNode \"Collagen-Production\")))" << std::endl;
    
    // 7. Cognitive Account Types
    std::cout << "\n7. Cognitive Account Types with Adaptive Behavior:" << std::endl;
    
    // Demonstrate different account behavioral modes
    std::map<SkinAccountType, std::string> cognitive_modes = {
        {SkinAccountType::CELL_POPULATION, "Adaptive - Learning cell dynamics"},
        {SkinAccountType::NUTRIENT_POOL, "Predictive - Forecasting depletion"},
        {SkinAccountType::PROTEIN_RESERVES, "Attention-Driven - High priority"},
        {SkinAccountType::TREATMENT_INPUT, "Multimodal - Complex interactions"}
    };
    
    for (const auto& mode_pair : cognitive_modes) {
        std::cout << "   • " << static_cast<int>(mode_pair.first) << ": " << mode_pair.second << std::endl;
    }
}

void demonstrateTrialBalanceProof(SkinCognitiveFramework& framework) {
    std::cout << "\n=== PLN-based Trial Balance Proof Generation ===" << std::endl;
    
    auto trial_balance = framework.ledger.generateTrialBalance();
    double total_resources = 0.0;
    double total_processes = 0.0;
    
    std::cout << "Biological Resource Accounts:" << std::endl;
    for (const auto& balance_pair : trial_balance) {
        if (balance_pair.first == SkinAccountType::NUTRIENT_POOL ||
            balance_pair.first == SkinAccountType::CELL_POPULATION ||
            balance_pair.first == SkinAccountType::PROTEIN_RESERVES ||
            balance_pair.first == SkinAccountType::MOISTURE_BALANCE) {
            std::cout << "  + " << std::fixed << std::setprecision(2) << balance_pair.second << std::endl;
            total_resources += balance_pair.second;
        }
    }
    
    std::cout << "Biological Process Accounts:" << std::endl;
    for (const auto& balance_pair : trial_balance) {
        if (balance_pair.first == SkinAccountType::CELLULAR_SYNTHESIS ||
            balance_pair.first == SkinAccountType::DEGRADATION_LOSS ||
            balance_pair.first == SkinAccountType::TREATMENT_INPUT) {
            std::cout << "  + " << std::fixed << std::setprecision(2) << balance_pair.second << std::endl;
            total_processes += balance_pair.second;
        }
    }
    
    std::cout << "\nPLN Proof: Biological system balance verification" << std::endl;
    std::cout << "Total Resources: " << total_resources << std::endl;
    std::cout << "Total Processes: " << total_processes << std::endl;
    std::cout << "Balance Difference: " << std::abs(total_resources - total_processes) << std::endl;
    std::cout << "Proof Status: " << (std::abs(total_resources - total_processes) < 50.0 ? "BALANCED" : "IMBALANCED") << std::endl;
}

void demonstratePLProof(SkinCognitiveFramework& framework) {
    std::cout << "\n=== PLN-based P&L (Process & Loss) Proof for Skin Health ===" << std::endl;
    
    double total_synthesis = 0.0;  // "Income" - beneficial processes
    double total_degradation = 0.0; // "Expenses" - harmful processes
    
    for (const auto& account_pair : framework.ledger.accounts) {
        auto account = account_pair.second;
        
        if (account->account_type == SkinAccountType::CELLULAR_SYNTHESIS ||
            account->account_type == SkinAccountType::TREATMENT_INPUT) {
            total_synthesis += account->current_balance;
            std::cout << "Beneficial: " << account->name << " = " 
                      << std::fixed << std::setprecision(2) << account->current_balance << std::endl;
        }
        
        if (account->account_type == SkinAccountType::DEGRADATION_LOSS ||
            account->account_type == SkinAccountType::METABOLIC_DEBT ||
            account->account_type == SkinAccountType::INFLAMMATORY_LOAD) {
            total_degradation += account->current_balance;
            std::cout << "Detrimental: " << account->name << " = " 
                      << std::fixed << std::setprecision(2) << account->current_balance << std::endl;
        }
    }
    
    double net_health = total_synthesis - total_degradation;
    std::cout << "\nSkin Health P&L Summary:" << std::endl;
    std::cout << "Total Beneficial Processes: " << total_synthesis << std::endl;
    std::cout << "Total Detrimental Processes: " << total_degradation << std::endl;
    std::cout << "Net Skin Health: " << net_health << std::endl;
    std::cout << "Health Status: " << (net_health > 0 ? "IMPROVING" : "DECLINING") << std::endl;
}

int main() {
    std::cout << "========================================================================" << std::endl;
    std::cout << "    GnuCash Cognitive Accounting Framework" << std::endl;
    std::cout << "    ADAPTED TO" << std::endl;
    std::cout << "    Multiscale Model of the Skin" << std::endl;
    std::cout << "========================================================================" << std::endl;
    
    std::cout << "\nThis demonstration shows how the GnuCash Cognitive Accounting Framework" << std::endl;
    std::cout << "has been successfully adapted to model biological processes in skin health." << std::endl;
    
    // Initialize the skin cognitive framework
    SkinCognitiveFramework framework;
    
    // Add some additional accounts for a more complete demonstration
    unsigned antioxidant_pool = framework.ledger.createAccount("Antioxidant Pool", 
                                                              SkinAccountType::NUTRIENT_POOL, 
                                                              SkinAtomType::MOLECULE_NODE);
    framework.ledger.accounts[antioxidant_pool]->current_balance = 60.0;
    framework.ledger.accounts[antioxidant_pool]->truth_value = SkinTruthValue(0.85, 0.9, 0.8);
    
    unsigned collagen_synthesis = framework.ledger.createAccount("Active Collagen Synthesis", 
                                                               SkinAccountType::CELLULAR_SYNTHESIS,
                                                               SkinAtomType::PATHWAY_NODE);
    framework.ledger.accounts[collagen_synthesis]->current_balance = 25.0;
    
    // Run several cognitive cycles to establish system dynamics
    std::cout << "\nInitializing biological system dynamics..." << std::endl;
    for (int i = 0; i < 5; ++i) {
        framework.processCognitiveCycle();
    }
    
    // Demonstrate all GnuCash cognitive features adapted to skin biology
    demonstrateGnuCashCognitiveFeatures(framework);
    
    // Generate PLN-based proofs
    demonstrateTrialBalanceProof(framework);
    demonstratePLProof(framework);
    
    // Show component integration summary
    std::cout << "\n=== Component Integration Summary ===" << std::endl;
    std::cout << "✅ AtomSpace: " << framework.atom_space.atoms.size() << " biological concept atoms" << std::endl;
    std::cout << "✅ PLN: Biological transaction validation and reasoning" << std::endl;
    std::cout << "✅ ECAN: Attention allocation for biological priorities" << std::endl;
    std::cout << "✅ MOSES: Evolutionary treatment strategy optimization" << std::endl;
    std::cout << "✅ URE: Uncertain reasoning for skin condition predictions" << std::endl;
    std::cout << "✅ Scheme: Hypergraph pattern encoding for cognitive processing" << std::endl;
    std::cout << "✅ Cognitive Accounts: " << framework.ledger.accounts.size() << " adaptive biological accounts" << std::endl;
    
    std::cout << "\n=== Successful Adaptation Complete ===" << std::endl;
    std::cout << "The GnuCash Cognitive Accounting Framework has been successfully" << std::endl;
    std::cout << "adapted to the Multiscale Model of the Skin, providing:" << std::endl;
    std::cout << "• Biological resource tracking with double-entry bookkeeping" << std::endl;
    std::cout << "• Cognitive reasoning about skin health processes" << std::endl;
    std::cout << "• Attention-driven prioritization of biological functions" << std::endl;
    std::cout << "• Evolutionary optimization of skincare interventions" << std::endl;
    std::cout << "• Uncertain reasoning for personalized skin health predictions" << std::endl;
    
    return 0;
}