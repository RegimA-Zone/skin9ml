#ifndef _RR_SIMULATOR_HPP_
#define _RR_SIMULATOR_HPP_

#include <simulator/simulator.hpp>
#include <relevance_realization.hpp>

namespace plingua { namespace rr {

// Enhanced simulator that transforms P-systems into RR hypergraphs
class RRSimulator {
public:
    RRSimulator() : time_step(0.1), rr_enabled(true), hypergraph(nullptr) {}
    virtual ~RRSimulator() { delete hypergraph; }
    
    // Initialize RR hypergraph from P-system configuration
    void initializeRRHypergraph() {
        if (!rr_enabled) return;
        
        delete hypergraph; // Clean up any existing hypergraph
        hypergraph = new RRHypergraph();
        
        // Create simple test environment for demo
        unsigned env_node = hypergraph->addMembraneNode(0, "environment", AARType::ARENA);
        membrane_to_node[0] = env_node;
        
        // Add a few test membranes
        unsigned agent_node = hypergraph->addMembraneNode(1, "agent_membrane", AARType::AGENT);
        unsigned arena_node = hypergraph->addMembraneNode(2, "arena_membrane", AARType::ARENA);
        
        membrane_to_node[1] = agent_node;
        membrane_to_node[2] = arena_node;
        
        // Create test relations
        hypergraph->addRelationEdge(agent_node, arena_node, RREdge::CO_CONSTRUCTION, 0.7);
    }
    
    // Run RR dynamics step
    void stepRRDynamics() {
        if (hypergraph && rr_enabled) {
            hypergraph->updateRelevanceRealization(time_step);
        }
    }
    
    // Enable/disable RR processing
    void setRREnabled(bool enabled) { rr_enabled = enabled; }
    bool isRREnabled() const { return rr_enabled; }
    
    // Get the RR hypergraph for analysis
    const RRHypergraph* getRRHypergraph() const { return hypergraph; }
    
    // Compute overall system relevance
    double computeSystemRelevance() const {
        if (!hypergraph) return 0.0;
        
        double total_relevance = 0.0;
        size_t node_count = 0;
        
        for (auto it = hypergraph->nodes.begin(); it != hypergraph->nodes.end(); ++it) {
            total_relevance += it->second->computeRelevanceGradient();
            ++node_count;
        }
        
        return node_count > 0 ? total_relevance / node_count : 0.0;
    }
    
    // Get emergent patterns detected
    std::vector<std::string> getEmergentPatterns() const {
        std::vector<std::string> patterns;
        
        if (!hypergraph) return patterns;
        
        // Look for high-relevance clusters
        for (auto it = hypergraph->nodes.begin(); it != hypergraph->nodes.end(); ++it) {
            auto node = it->second;
            if (node->salience > 0.8 && node->affordance_realization > 0.7) {
                std::string type_str = (node->aarType == AARType::AGENT ? "agent" : 
                                      node->aarType == AARType::ARENA ? "arena" : "relation");
                patterns.push_back(std::string("High-relevance ") + type_str + " node: " + node->label);
            }
        }
        
        return patterns;
    }

private:
    RRHypergraph* hypergraph;
    double time_step;
    bool rr_enabled;
    
    // Mappings between P-system and RR components
    std::map<unsigned, unsigned> membrane_to_node;  // membrane_id -> node_id
    std::map<unsigned, unsigned> rule_to_node;      // rule_id -> node_id
    std::map<std::string, unsigned> object_to_node; // object_name -> node_id
};

}} // namespace plingua::rr

#endif // _RR_SIMULATOR_HPP_