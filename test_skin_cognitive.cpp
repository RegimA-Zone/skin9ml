#include <iostream>
#include <iomanip>
#include "skin_cognitive_framework.hpp"

using namespace plingua::skin;
using namespace plingua::atomspace;
using namespace plingua::rr;

void printSkinAccountState(const SkinLedger& ledger) {
    std::cout << "\n=== Skin Biological Accounts State ===" << std::endl;
    
    for (const auto& account_pair : ledger.accounts) {
        auto account = account_pair.second;
        std::cout << "Account: " << account->name << " (ID: " << account->id << ")" << std::endl;
        std::cout << "  Type: " << static_cast<int>(account->account_type) << std::endl;
        std::cout << "  Current Balance: " << std::fixed << std::setprecision(2) 
                  << account->current_balance << "/" << account->capacity_limit << std::endl;
        std::cout << "  Health Score: " << std::setprecision(3) << account->computeHealthScore() << std::endl;
        std::cout << "  STI: " << account->short_term_importance 
                  << ", LTI: " << account->long_term_importance << std::endl;
        std::cout << "  Truth Value: [bio=" << account->truth_value.biological_strength
                  << ", clin=" << account->truth_value.clinical_confidence
                  << ", indiv=" << account->truth_value.individual_relevance << "]" << std::endl;
        std::cout << std::endl;
    }
}

void printTrialBalance(const SkinLedger& ledger) {
    std::cout << "\n=== Skin Biological Trial Balance ===" << std::endl;
    auto trial_balance = ledger.generateTrialBalance();
    
    std::map<SkinAccountType, std::string> type_names = {
        {SkinAccountType::NUTRIENT_POOL, "Nutrient Pools"},
        {SkinAccountType::CELL_POPULATION, "Cell Populations"},
        {SkinAccountType::PROTEIN_RESERVES, "Protein Reserves"},
        {SkinAccountType::MOISTURE_BALANCE, "Moisture Balance"},
        {SkinAccountType::METABOLIC_DEBT, "Metabolic Debt"},
        {SkinAccountType::INFLAMMATORY_LOAD, "Inflammatory Load"},
        {SkinAccountType::REPAIR_OBLIGATION, "Repair Obligations"},
        {SkinAccountType::CELLULAR_SYNTHESIS, "Cellular Synthesis"},
        {SkinAccountType::DEGRADATION_LOSS, "Degradation Loss"},
        {SkinAccountType::ENVIRONMENTAL_IMPACT, "Environmental Impact"},
        {SkinAccountType::TREATMENT_INPUT, "Treatment Input"}
    };
    
    for (const auto& balance_pair : trial_balance) {
        auto type_name = type_names.find(balance_pair.first);
        std::string name = (type_name != type_names.end()) ? type_name->second : "Unknown";
        std::cout << "  " << name << ": " << std::fixed << std::setprecision(2) 
                  << balance_pair.second << std::endl;
    }
}

void simulateSkinAging(SkinCognitiveFramework& framework) {
    std::cout << "\n=== Simulating Skin Aging Process ===" << std::endl;
    
    // Create aging-related transactions
    SkinTransaction collagen_degradation(
        1, "Age-related collagen breakdown", SkinTransactionType::PROTEIN_SYNTHESIS,
        0, 0, 5.0  // Lose 5 units of collagen
    );
    collagen_degradation.efficiency = 0.9;
    collagen_degradation.truth_value = SkinTruthValue(0.9, 0.8, 0.7); // Well-documented aging process
    
    // Find collagen account
    for (auto& account_pair : framework.ledger.accounts) {
        if (account_pair.second->name == "Collagen Reserves") {
            collagen_degradation.from_account_id = account_pair.second->id;
            // Create degradation sink account
            unsigned degradation_account = framework.ledger.createAccount(
                "Collagen Degradation", SkinAccountType::DEGRADATION_LOSS, SkinAtomType::PATHWAY_NODE);
            collagen_degradation.to_account_id = degradation_account;
            break;
        }
    }
    
    // Process aging transaction
    bool aging_processed = framework.ledger.processTransaction(collagen_degradation);
    std::cout << "Collagen degradation processed: " << (aging_processed ? "Yes" : "No") << std::endl;
}

void simulateSkincareIntervention(SkinCognitiveFramework& framework) {
    std::cout << "\n=== Simulating Skincare Intervention ===" << std::endl;
    
    // Create vitamin C treatment
    unsigned vitamin_c_treatment = framework.ledger.createAccount(
        "Vitamin C Serum", SkinAccountType::TREATMENT_INPUT, SkinAtomType::TREATMENT_NODE);
    framework.ledger.accounts[vitamin_c_treatment]->current_balance = 50.0;
    framework.ledger.accounts[vitamin_c_treatment]->truth_value = SkinTruthValue(0.8, 0.9, 0.85);
    
    // Create treatment transaction to boost vitamin C pool
    SkinTransaction treatment_application(
        2, "Vitamin C serum application", SkinTransactionType::NUTRIENT_TRANSFER,
        vitamin_c_treatment, 0, 25.0
    );
    treatment_application.efficiency = 0.7; // 70% bioavailability
    treatment_application.truth_value = SkinTruthValue(0.7, 0.8, 0.9);
    
    // Find vitamin C pool account
    for (auto& account_pair : framework.ledger.accounts) {
        if (account_pair.second->name == "Vitamin C Pool") {
            treatment_application.to_account_id = account_pair.second->id;
            break;
        }
    }
    
    bool treatment_processed = framework.ledger.processTransaction(treatment_application);
    std::cout << "Vitamin C treatment processed: " << (treatment_processed ? "Yes" : "No") << std::endl;
}

int main() {
    std::cout << "=== Skin Cognitive Accounting Framework Demo ===" << std::endl;
    std::cout << "Adapting GnuCash Cognitive Framework to Multiscale Skin Model" << std::endl;
    
    // Initialize skin cognitive framework
    SkinCognitiveFramework framework;
    
    std::cout << "\n1. Initial Healthy Skin State:" << std::endl;
    printSkinAccountState(framework.ledger);
    printTrialBalance(framework.ledger);
    
    // Simulate biological processes for several cycles
    std::cout << "\n2. Running 10 biological processing cycles..." << std::endl;
    for (int i = 0; i < 10; ++i) {
        framework.processCognitiveCycle();
        
        if ((i + 1) % 5 == 0) {
            std::cout << "\n--- After " << (i + 1) << " cycles ---" << std::endl;
            printTrialBalance(framework.ledger);
        }
    }
    
    // Simulate aging process
    simulateSkinAging(framework);
    std::cout << "\nAfter aging simulation:" << std::endl;
    printSkinAccountState(framework.ledger);
    
    // Apply skincare intervention
    simulateSkincareIntervention(framework);
    std::cout << "\nAfter skincare intervention:" << std::endl;
    printSkinAccountState(framework.ledger);
    
    // Generate biological insights using PLN
    std::cout << "\n=== Biological Insights from PLN Reasoning ===" << std::endl;
    auto insights = framework.ledger.generateBiologicalInsights();
    for (const auto& insight : insights) {
        std::cout << "  • " << insight << std::endl;
    }
    
    // Test MOSES treatment optimization
    std::cout << "\n=== Treatment Optimization using MOSES ===" << std::endl;
    for (auto& account_pair : framework.ledger.accounts) {
        if (account_pair.second->account_type == SkinAccountType::PROTEIN_RESERVES &&
            account_pair.second->computeHealthScore() < 0.8) {
            auto recommendations = framework.ledger.optimizeTreatmentStrategy(account_pair.second->id);
            std::cout << "Treatment recommendations for " << account_pair.second->name << ":" << std::endl;
            for (unsigned rec_id : recommendations) {
                auto rec_account = framework.ledger.accounts.find(rec_id);
                if (rec_account != framework.ledger.accounts.end()) {
                    std::cout << "  • " << rec_account->second->name << std::endl;
                }
            }
        }
    }
    
    // Display final AtomSpace integration
    std::cout << "\n=== AtomSpace Integration Status ===" << std::endl;
    std::cout << "Total atoms in skin cognitive system: " << framework.atom_space.atoms.size() << std::endl;
    
    auto concept_nodes = framework.atom_space.findAtomsOfType(Atom::CONCEPT_NODE);
    std::cout << "Skin-related concept nodes: " << concept_nodes.size() << std::endl;
    for (unsigned id : concept_nodes) {
        auto atom = framework.atom_space.getAtom(id);
        if (atom) {
            std::cout << "  " << atom->name 
                      << " [strength=" << std::fixed << std::setprecision(3) << atom->strength
                      << ", confidence=" << atom->confidence << "]" << std::endl;
        }
    }
    
    // Final system summary
    std::cout << "\n=== System Summary ===" << std::endl;
    std::cout << "Successfully integrated GnuCash Cognitive Accounting with Skin Biology:" << std::endl;
    std::cout << "• " << framework.ledger.accounts.size() << " biological accounts tracking skin resources" << std::endl;
    std::cout << "• " << framework.ledger.transactions.size() << " biological transactions processed" << std::endl;
    std::cout << "• AtomSpace with " << framework.atom_space.atoms.size() << " cognitive atoms" << std::endl;
    std::cout << "• PLN inference providing biological insights" << std::endl;
    std::cout << "• ECAN attention allocation for biological priorities" << std::endl;
    std::cout << "• MOSES optimization for treatment strategies" << std::endl;
    std::cout << "• URE reasoning for skin condition predictions" << std::endl;
    
    return 0;
}