# RR-PLingua Usage Examples and Integration Guide

This document provides comprehensive examples of using the RR-enhanced membrane computing framework, demonstrating all four major implementation areas with practical code examples and use cases.

## Quick Start Example

### Basic RR-Enhanced Membrane System

```cpp
#include <relevance_realization.hpp>
#include <atomspace_integration.hpp>

using namespace plingua::rr;
using namespace plingua::atomspace;

int main() {
    // Create RR hypergraph
    RRHypergraph hypergraph;
    
    // Add agent and arena membranes
    unsigned agent = hypergraph.addMembraneNode(1, "cognitive_agent", AARType::AGENT);
    unsigned arena = hypergraph.addMembraneNode(2, "task_environment", AARType::ARENA);
    
    // Create co-construction relation
    hypergraph.addRelationEdge(agent, arena, RREdge::CO_CONSTRUCTION, 0.7);
    
    // Setup AtomSpace integration
    AtomSpace atomspace;
    RRAtomSpaceIntegrator integrator(&hypergraph, &atomspace);
    
    // Run RR dynamics for 10 steps
    for (int i = 0; i < 10; ++i) {
        hypergraph.updateRelevanceRealization(0.1);
        integrator.performIntegration();
    }
    
    // Find emergent patterns
    auto patterns = integrator.findEmergentPatterns();
    for (const auto& pattern : patterns) {
        std::cout << "Detected: " << pattern << std::endl;
    }
    
    return 0;
}
```

## Advanced PLN Integration Examples

### 1. PLN Truth Value Operations

```cpp
#include <pln_integration.hpp>

using namespace plingua::pln;

void demonstratePLNOperations() {
    // Create PLN truth values
    PLNTruthValue agent_belief(0.8, 0.9);      // High strength, high confidence
    PLNTruthValue arena_state(0.6, 0.7);      // Medium strength, good confidence
    
    // Perform PLN operations
    auto conjunction = agent_belief.conjunction(arena_state);
    std::cout << "Conjunction: strength=" << conjunction.strength 
              << ", confidence=" << conjunction.confidence << std::endl;
    
    auto implication = agent_belief.implication(arena_state);
    std::cout << "Implication: strength=" << implication.strength 
              << ", confidence=" << implication.confidence << std::endl;
    
    auto negation = agent_belief.negate();
    std::cout << "Negation: strength=" << negation.strength 
              << ", confidence=" << negation.confidence << std::endl;
}
```

### 2. PLN Inference Engine Usage

```cpp
void demonstratePLNInference() {
    RRHypergraph hypergraph;
    AtomSpace atomspace;
    PLNInferenceEngine pln_engine(&atomspace);
    
    // Create high-coupling agent-arena pair
    unsigned agent = hypergraph.addMembraneNode(1, "learning_agent", AARType::AGENT);
    unsigned arena = hypergraph.addMembraneNode(2, "learning_environment", AARType::ARENA);
    hypergraph.addRelationEdge(agent, arena, RREdge::CO_CONSTRUCTION, 0.85);
    
    // Integrate with AtomSpace
    RRAtomSpaceIntegrator integrator(&hypergraph, &atomspace);
    integrator.performIntegration();
    
    // Generate RR-based implications
    pln_engine.generateRRImplications(&hypergraph);
    
    // Perform deduction
    auto deductions = pln_engine.performDeduction();
    std::cout << "Generated " << deductions.size() << " new deductions" << std::endl;
    
    // Perform abduction (hypothesis generation)
    auto abductions = pln_engine.performAbduction();
    std::cout << "Generated " << abductions.size() << " new hypotheses" << std::endl;
    
    // Full inference cycle
    pln_engine.performInferenceCycle(&hypergraph);
    auto results = pln_engine.getInferenceResults();
    
    for (const auto& result : results) {
        std::cout << "PLN Result: " << result << std::endl;
    }
}
```

## Scheme Interface Examples

### 1. Interactive REPL Session

```cpp
#include <scheme_interface.hpp>

using namespace plingua::scheme;

void interactiveSchemeSession() {
    RRHypergraph hypergraph;
    AtomSpace atomspace;
    
    // Setup test environment
    unsigned agent = hypergraph.addMembraneNode(1, "interactive_agent", AARType::AGENT);
    unsigned arena = hypergraph.addMembraneNode(2, "interactive_arena", AARType::ARENA);
    hypergraph.addRelationEdge(agent, arena, RREdge::INTERACTION, 0.75);
    
    // Setup AtomSpace integration
    RRAtomSpaceIntegrator integrator(&hypergraph, &atomspace);
    integrator.performIntegration();
    
    // Create Scheme evaluator
    SchemeEvaluator evaluator(&hypergraph, &atomspace);
    
    // Start interactive REPL
    std::cout << "Starting Scheme REPL..." << std::endl;
    evaluator.startREPL();  // This will run interactively
}
```

### 2. Programmatic Scheme Commands

```cpp
void programmaticSchemeCommands() {
    RRHypergraph hypergraph;
    AtomSpace atomspace;
    SchemeEvaluator evaluator(&hypergraph, &atomspace);
    
    // Execute various Scheme commands programmatically
    std::vector<std::string> commands = {
        "(list-rr-nodes)",
        "(get-system-relevance)",
        "(find-patterns)",
        "(get-salience node-1)",
        "(update-salience node-1 0.9)",
        "(run-pln-inference)",
        "(find-atom \"agent\")"
    };
    
    for (const auto& cmd : commands) {
        std::string result = evaluator.evaluate(cmd);
        std::cout << "Command: " << cmd << std::endl;
        std::cout << "Result: " << result << std::endl << std::endl;
    }
}
```

## Persistent Storage Examples

### 1. Basic Save and Load Operations

```cpp
#include <persistent_atomspace.hpp>

using namespace plingua::persistent;

void demonstratePersistence() {
    RRHypergraph hypergraph;
    AtomSpace atomspace;
    PersistentAtomSpace storage;
    
    // Create and populate system
    unsigned agent = hypergraph.addMembraneNode(1, "persistent_agent", AARType::AGENT);
    unsigned arena = hypergraph.addMembraneNode(2, "persistent_arena", AARType::ARENA);
    hypergraph.addRelationEdge(agent, arena, RREdge::CO_CONSTRUCTION, 0.8);
    
    RRAtomSpaceIntegrator integrator(&hypergraph, &atomspace);
    integrator.performIntegration();
    
    // Save to files
    bool atomspace_saved = storage.saveToFile(&atomspace, "system_atomspace.json");
    bool rr_saved = storage.saveRRHypergraph(&hypergraph, "system_rr_hypergraph.json");
    
    std::cout << "AtomSpace saved: " << (atomspace_saved ? "Success" : "Failed") << std::endl;
    std::cout << "RR Hypergraph saved: " << (rr_saved ? "Success" : "Failed") << std::endl;
    
    // Load from files
    AtomSpace loaded_atomspace;
    RRHypergraph loaded_hypergraph;
    
    bool atomspace_loaded = storage.loadFromFile(&loaded_atomspace, "system_atomspace.json");
    bool rr_loaded = storage.loadRRHypergraph(&loaded_hypergraph, "system_rr_hypergraph.json");
    
    std::cout << "AtomSpace loaded: " << (atomspace_loaded ? "Success" : "Failed") << std::endl;
    std::cout << "RR Hypergraph loaded: " << (rr_loaded ? "Success" : "Failed") << std::endl;
}
```

### 2. Memory Consolidation and Incremental Learning

```cpp
void demonstrateMemoryConsolidation() {
    AtomSpace atomspace;
    PersistentAtomSpace storage;
    
    // Create atoms with varying confidence levels
    unsigned high_conf_atom = atomspace.addConceptNode("reliable_knowledge", 0.9, 0.95);
    unsigned med_conf_atom = atomspace.addConceptNode("uncertain_knowledge", 0.6, 0.4);
    unsigned low_conf_atom = atomspace.addConceptNode("unreliable_knowledge", 0.3, 0.1);
    
    std::cout << "Before consolidation: " << atomspace.atoms.size() << " atoms" << std::endl;
    
    // Consolidate memory (remove atoms with confidence < 0.3)
    storage.consolidateMemory(&atomspace, 0.3);
    
    std::cout << "After consolidation: " << atomspace.atoms.size() << " atoms" << std::endl;
    
    // Demonstrate incremental learning
    AtomSpace new_experience;
    unsigned new_atom = new_experience.addConceptNode("new_knowledge", 0.8, 0.85);
    
    // Merge new experience with existing knowledge
    storage.mergeAtomSpaces(&atomspace, &new_experience);
    
    std::cout << "After merging new experience: " << atomspace.atoms.size() << " atoms" << std::endl;
}
```

## Multi-Level Integration Examples

### 1. Hierarchical Membrane Structure

```cpp
void demonstrateHierarchicalStructure() {
    RRHypergraph hypergraph;
    
    // Create hierarchical structure
    unsigned environment = hypergraph.addMembraneNode(0, "global_environment", AARType::ARENA);
    
    // Level 1: Outer membranes
    unsigned outer_agent = hypergraph.addMembraneNode(1, "outer_cognitive_system", AARType::AGENT);
    unsigned outer_arena = hypergraph.addMembraneNode(2, "outer_task_domain", AARType::ARENA);
    
    // Level 2: Inner membranes
    unsigned inner_agent1 = hypergraph.addMembraneNode(3, "perception_module", AARType::AGENT);
    unsigned inner_agent2 = hypergraph.addMembraneNode(4, "action_module", AARType::AGENT);
    unsigned inner_arena1 = hypergraph.addMembraneNode(5, "sensory_space", AARType::ARENA);
    unsigned inner_arena2 = hypergraph.addMembraneNode(6, "motor_space", AARType::ARENA);
    
    // Create hierarchical relations
    hypergraph.addRelationEdge(environment, outer_agent, RREdge::CO_CONSTRUCTION, 0.6);
    hypergraph.addRelationEdge(environment, outer_arena, RREdge::CO_CONSTRUCTION, 0.6);
    hypergraph.addRelationEdge(outer_agent, outer_arena, RREdge::INTERACTION, 0.8);
    
    hypergraph.addRelationEdge(outer_agent, inner_agent1, RREdge::CO_CONSTRUCTION, 0.7);
    hypergraph.addRelationEdge(outer_agent, inner_agent2, RREdge::CO_CONSTRUCTION, 0.7);
    hypergraph.addRelationEdge(outer_arena, inner_arena1, RREdge::CO_CONSTRUCTION, 0.7);
    hypergraph.addRelationEdge(outer_arena, inner_arena2, RREdge::CO_CONSTRUCTION, 0.7);
    
    hypergraph.addRelationEdge(inner_agent1, inner_arena1, RREdge::INTERACTION, 0.9);
    hypergraph.addRelationEdge(inner_agent2, inner_arena2, RREdge::INTERACTION, 0.9);
    
    std::cout << "Created hierarchical structure with " << hypergraph.nodes.size() << " nodes" << std::endl;
    std::cout << "and " << hypergraph.edges.size() << " edges" << std::endl;
    
    // Run multi-level dynamics
    for (int i = 0; i < 20; ++i) {
        hypergraph.updateRelevanceRealization(0.05);
    }
    
    // Analyze cross-level emergence
    double outer_salience = hypergraph.nodes[outer_agent]->salience;
    double inner_coherence = (hypergraph.nodes[inner_agent1]->computeTrialecticCoherence() + 
                             hypergraph.nodes[inner_agent2]->computeTrialecticCoherence()) / 2.0;
    
    if (outer_salience > 0.6 && inner_coherence > 0.3) {
        std::cout << "Cross-level emergence detected!" << std::endl;
        std::cout << "Outer salience: " << outer_salience << std::endl;
        std::cout << "Inner coherence: " << inner_coherence << std::endl;
    }
}
```

### 2. Temporal Reasoning and Evolution Tracking

```cpp
void demonstrateTemporalReasoning() {
    RRHypergraph hypergraph;
    
    // Create simple agent-arena system
    unsigned agent = hypergraph.addMembraneNode(1, "evolving_agent", AARType::AGENT);
    unsigned arena = hypergraph.addMembraneNode(2, "changing_arena", AARType::ARENA);
    hypergraph.addRelationEdge(agent, arena, RREdge::CO_CONSTRUCTION, 0.5);
    
    // Track system evolution over time
    std::vector<double> temporal_relevance;
    std::vector<double> temporal_coupling;
    
    for (int t = 0; t < 50; ++t) {
        hypergraph.updateRelevanceRealization(0.1);
        
        // Calculate system-wide relevance
        double total_relevance = 0.0;
        for (auto it = hypergraph.nodes.begin(); it != hypergraph.nodes.end(); ++it) {
            total_relevance += it->second->computeRelevanceGradient();
        }
        double avg_relevance = total_relevance / hypergraph.nodes.size();
        temporal_relevance.push_back(avg_relevance);
        
        // Calculate coupling strength
        double coupling = hypergraph.computeCouplingStrength(agent, arena);
        temporal_coupling.push_back(coupling);
        
        if (t % 10 == 0) {
            std::cout << "Time " << t << ": relevance=" << avg_relevance 
                      << ", coupling=" << coupling << std::endl;
        }
    }
    
    // Analyze temporal trends
    if (temporal_relevance.size() >= 10) {
        double recent_avg = 0.0, earlier_avg = 0.0;
        for (int i = 0; i < 10; ++i) {
            recent_avg += temporal_relevance[temporal_relevance.size() - 1 - i];
            earlier_avg += temporal_relevance[i];
        }
        recent_avg /= 10;
        earlier_avg /= 10;
        
        double trend = recent_avg - earlier_avg;
        std::cout << "Temporal trend: " << (trend > 0.01 ? "increasing" : 
                                          trend < -0.01 ? "decreasing" : "stable") 
                  << " (Δ=" << trend << ")" << std::endl;
    }
}
```

## Complete Integration Example

### Full RR-RNN System Demonstration

```cpp
#include <relevance_realization.hpp>
#include <atomspace_integration.hpp>
#include <pln_integration.hpp>
#include <scheme_interface.hpp>
#include <persistent_atomspace.hpp>

void fullSystemDemo() {
    std::cout << "=== Full RR-RNN System Demonstration ===" << std::endl;
    
    // Initialize all components
    RRHypergraph hypergraph;
    AtomSpace atomspace;
    RRAtomSpaceIntegrator integrator(&hypergraph, &atomspace);
    PLNInferenceEngine pln_engine(&atomspace);
    SchemeEvaluator scheme_eval(&hypergraph, &atomspace);
    PersistentAtomSpace storage;
    
    // Create test environment
    unsigned env = hypergraph.addMembraneNode(0, "test_environment", AARType::ARENA);
    unsigned agent = hypergraph.addMembraneNode(1, "cognitive_agent", AARType::AGENT);
    unsigned arena = hypergraph.addMembraneNode(2, "task_arena", AARType::ARENA);
    
    hypergraph.addRelationEdge(env, agent, RREdge::INTERACTION, 0.5);
    hypergraph.addRelationEdge(agent, arena, RREdge::CO_CONSTRUCTION, 0.7);
    
    // Phase 1: RR Dynamics Evolution
    std::cout << "\n--- Phase 1: RR Dynamics ---" << std::endl;
    for (int i = 0; i < 15; ++i) {
        hypergraph.updateRelevanceRealization(0.1);
        if (i % 5 == 0) {
            integrator.performIntegration();
            auto patterns = integrator.findEmergentPatterns();
            if (!patterns.empty()) {
                std::cout << "Step " << i << " - Emergent patterns: " << patterns.size() << std::endl;
            }
        }
    }
    
    // Phase 2: PLN Integration
    std::cout << "\n--- Phase 2: PLN Integration ---" << std::endl;
    pln_engine.generateRRImplications(&hypergraph);
    pln_engine.performInferenceCycle(&hypergraph);
    auto pln_results = pln_engine.getInferenceResults();
    
    for (const auto& result : pln_results) {
        std::cout << "PLN: " << result << std::endl;
    }
    
    // Phase 3: Scheme Interface
    std::cout << "\n--- Phase 3: Scheme Interface ---" << std::endl;
    std::vector<std::string> demo_commands = {
        "(get-system-relevance)",
        "(find-patterns)",
        "(run-pln-inference)",
        "(list-rr-nodes)"
    };
    
    for (const auto& cmd : demo_commands) {
        std::string result = scheme_eval.evaluate(cmd);
        std::cout << "scheme> " << cmd << std::endl;
        std::cout << result << std::endl;
    }
    
    // Phase 4: Persistence
    std::cout << "\n--- Phase 4: Persistence ---" << std::endl;
    bool atomspace_saved = storage.saveToFile(&atomspace, "/tmp/full_demo_atomspace.json");
    bool rr_saved = storage.saveRRHypergraph(&hypergraph, "/tmp/full_demo_rr.json");
    
    std::cout << "System state saved: " 
              << (atomspace_saved && rr_saved ? "Success" : "Failed") << std::endl;
    
    // Memory consolidation
    size_t atoms_before = atomspace.atoms.size();
    storage.consolidateMemory(&atomspace, 0.3);
    size_t atoms_after = atomspace.atoms.size();
    
    std::cout << "Memory consolidation: " << atoms_before << " → " << atoms_after 
              << " atoms (removed " << (atoms_before - atoms_after) << ")" << std::endl;
    
    std::cout << "\n=== Full System Demo Complete ===" << std::endl;
}
```

## Performance Monitoring Examples

### System Performance Analysis

```cpp
void performanceAnalysis() {
    RRHypergraph hypergraph;
    AtomSpace atomspace;
    
    // Create larger test system
    const int num_agents = 10;
    const int num_arenas = 8;
    
    std::vector<unsigned> agents, arenas;
    
    for (int i = 0; i < num_agents; ++i) {
        agents.push_back(hypergraph.addMembraneNode(i, "agent_" + std::to_string(i), AARType::AGENT));
    }
    
    for (int i = 0; i < num_arenas; ++i) {
        arenas.push_back(hypergraph.addMembraneNode(100 + i, "arena_" + std::to_string(i), AARType::ARENA));
    }
    
    // Create connections
    for (unsigned agent : agents) {
        for (unsigned arena : arenas) {
            if (rand() % 100 < 30) { // 30% connection probability
                double strength = 0.3 + (rand() % 50) / 100.0;
                hypergraph.addRelationEdge(agent, arena, RREdge::INTERACTION, strength);
            }
        }
    }
    
    std::cout << "Created system with " << hypergraph.nodes.size() << " nodes and " 
              << hypergraph.edges.size() << " edges" << std::endl;
    
    // Performance timing
    auto start_time = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < 100; ++i) {
        hypergraph.updateRelevanceRealization(0.05);
    }
    
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    
    std::cout << "100 RR update cycles completed in " << duration.count() << " ms" << std::endl;
    std::cout << "Average per cycle: " << (duration.count() / 100.0) << " ms" << std::endl;
}
```

These comprehensive examples demonstrate the full capabilities of the RR-enhanced membrane computing framework, showing how to leverage all four major implementation areas for sophisticated cognitive architecture applications.