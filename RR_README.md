# Relevance Realization Extensions for P-Lingua

This directory contains the implementation of the Relevance Realization (RR) and Agent-Arena-Relation (AAR) architecture for P-Lingua, transforming P-systems into cognitive architectures inspired by John Vervaeke's work.

## Files

### Core Implementation
- `include/relevance_realization.hpp` - Core RR data structures and hypergraph implementation
- `include/rr_simulator.hpp` - Enhanced simulator with RR dynamics
- `examples/rr_trialectic_model.pli` - Sample P-Lingua^RR model demonstrating the trialectic architecture
- `examples/rr_simple_demo.cpp` - Standalone demo of RR functionality

### Key Features Implemented

1. **Hypergraph Representation**: P-systems transformed into living hypergraphs where:
   - Membranes → RR nodes with salience and affordance properties
   - Rules → Agent nodes with transformation capabilities
   - Objects → Arena nodes representing environmental contexts
   - Relations → Edges encoding agent-arena dynamics

2. **Agent-Arena-Relation (AAR) Mapping**:
   - **Agent**: Transformation rules and active membranes
   - **Arena**: Environmental membranes and object multisets
   - **Relation**: Interaction edges with co-construction dynamics

3. **Trialectic Architecture**: Implementation of Λ¹, Λ², Λ³ levels:
   - **Λ¹ (Autopoiesis)**: Self-maintaining membrane dynamics
   - **Λ² (Anticipation)**: Predictive projection capabilities
   - **Λ³ (Adaptation)**: Agent-arena co-construction

4. **Relevance Realization Dynamics**:
   - Salience tracking and update mechanisms
   - Affordance potential vs. realization computation
   - Relevance gradient: `∇ℜ = log(affordance_realization/affordance_potential)`
   - Recursive trialectic co-constitution: `∀^ω(x ⇔^α y ⇔^α z ⇔^α x)`

5. **Scheme-like Interface**: Functional programming style for RR construction:
   ```cpp
   // (make-rr-node 'agent '(rule "a+b->c" salience 0.8))
   auto agent = scheme_like::make_rr_node(RRNode::RULE, AARType::AGENT, "rule_bind", props);
   
   // (make-relation agent arena '(strength 0.5))
   auto relation = scheme_like::make_relation(agent_id, arena_id, rel_props);
   ```

6. **Emergent Pattern Detection**: Monitors for high-relevance agent-arena couplings

## Usage

### Running the Demo
```bash
cd /home/runner/work/rrpling/rrpling
g++ -std=c++11 -I./include -o rr_simple_demo examples/rr_simple_demo.cpp
./rr_simple_demo
```

### Theoretical Foundation

The implementation is based on the formal framework defined in:
- `Formal Grammar RR - Relevance Realization P-Systems.md`
- `Membrane Computing - Trialectic Architecture.md`
- `RR-math.md`
- `Unraveling the Triadic Architecture of Relevance Realization.md`

### Key Mathematical Concepts Implemented

1. **Trialectic State Space**: `Θ³_trialectic ⊂ ℂ^(ω×ω×ω)`
2. **Agent-Arena Co-construction**: `agent ↔^δ arena ∈ ℝ^(∞×∞)`
3. **Relevance Gradient**: `∇ℜ = lim_{t→∞} Σᵢ log(affordance_realizationᵢ(t)/affordance_potentialᵢ(t))`
4. **Non-Formalizability Preservation**: Maintains the non-algorithmic character through parallel execution

This implementation demonstrates how P-systems can serve as a computational substrate for exploring Vervaeke's cognitive science insights about relevance realization and wisdom cultivation.