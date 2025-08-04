# RR-RNN Process Flow Diagrams

This document contains PlantUML diagrams showing the detailed process flows of the RR-RNN system components.

## Overall System Process Flow

```plantuml
@startuml RR-RNN-System-Flow
!theme plain
title RR-RNN System Process Flow

actor User
participant "P-Lingua Parser" as Parser
participant "RR Hypergraph" as RR
participant "AtomSpace" as AS
participant "PLN Engine" as PLN
participant "Scheme REPL" as Scheme
participant "Persistent Storage" as Storage

== Initialization ==
User -> Parser: Load P-system definition
Parser -> RR: Create RR hypergraph from membranes
RR -> AS: Initialize AtomSpace integration
AS -> PLN: Setup PLN inference engine
PLN -> Scheme: Register command interface

== Runtime Dynamics ==
loop Continuous RR Evolution
    RR -> RR: Update trialectic states
    note right: ∀^ω(x ⇔^α y ⇔^α z ⇔^α x)
    
    RR -> RR: Compute relevance gradients
    note right: ∇ℜ = lim_{t→∞} Σᵢ log(aᵣᵢ(t)/aₚᵢ(t))
    
    RR -> AS: Synchronize node properties
    AS -> PLN: Generate new implications
    
    PLN -> PLN: Perform deduction cycle
    note right: A→B, A ⊢ B
    
    PLN -> PLN: Perform abduction cycle  
    note right: A→B, B ⊢ A (reduced confidence)
    
    PLN -> AS: Update truth values
    AS -> RR: Feedback relevance updates
    
    RR -> RR: Detect emergent patterns
    note right: Agent-arena coupling > threshold
end

== Interactive Exploration ==
User -> Scheme: Execute Scheme commands
alt Query Commands
    Scheme -> RR: (list-rr-nodes)
    RR -> Scheme: Return node properties
else Update Commands  
    Scheme -> RR: (update-salience node-ID value)
    RR -> AS: Propagate changes
    AS -> PLN: Trigger inference update
else Inference Commands
    Scheme -> PLN: (run-pln-inference)
    PLN -> AS: Execute inference cycle
    AS -> Scheme: Return inference results
end

Scheme -> User: Display results

== Persistence ==
User -> Storage: Save system state
Storage -> AS: Serialize AtomSpace to JSON
Storage -> RR: Serialize RR hypergraph to JSON
Storage -> Storage: Consolidate memory (remove low-confidence atoms)
Storage -> User: Confirm persistence complete

@enduml
```

## RR Trialectic Dynamics Process

```plantuml
@startuml RR-Trialectic-Process
!theme plain
title RR Trialectic Co-Constitution Process

participant "Agent Membrane" as Agent
participant "Arena Membrane" as Arena
participant "Relation Component" as Relation
participant "Trialectic Engine" as Engine

== Initial State ==
Agent -> Engine: Initial salience, affordance potential
Arena -> Engine: Initial salience, affordance potential  
Relation -> Engine: Initial coupling strength

== Trialectic Update Cycle ==
loop Continuous Evolution
    Engine -> Engine: Compute trialectic state vector
    note right: [x, y, z] representing agent-arena-relation
    
    Engine -> Agent: Update based on arena + relation influence
    note right: new_state[i] += coupling * (state[next] - state[prev]) / 2
    
    Engine -> Arena: Update based on agent + relation influence
    Engine -> Relation: Update based on agent + arena influence
    
    Agent -> Engine: Updated salience
    Arena -> Engine: Updated affordance realization
    Relation -> Engine: Updated coupling strength
    
    Engine -> Engine: Apply tanh normalization
    note right: Keep states bounded in [-1, 1]
    
    Engine -> Engine: Compute trialectic coherence
    note right: coherence = Σ(state[i] * state[next]) / n
    
    alt High Coherence (> 0.6)
        Engine -> Engine: Amplify co-constitution effects
        note right: Positive feedback loop
    else Low Coherence (< 0.3)
        Engine -> Engine: Dampen interactions
        note right: Prevent instability
    end
    
    Engine -> Engine: Update relevance gradient
    note right: ∇ℜ = log(affordance_realization / affordance_potential)
end

@enduml
```

## PLN Inference Process Flow

```plantuml
@startuml PLN-Inference-Process
!theme plain
title PLN Inference Engine Process Flow

participant "RR Hypergraph" as RR
participant "PLN Engine" as PLN
participant "AtomSpace" as AS
participant "Implication Generator" as ImpGen
participant "Deduction Engine" as Ded
participant "Abduction Engine" as Abd

== Implication Generation ==
RR -> PLN: High-coupling agent-arena pairs
PLN -> ImpGen: Agent-arena relationship data
ImpGen -> AS: Find corresponding atoms
AS -> ImpGen: Agent and arena atom IDs

ImpGen -> ImpGen: Calculate implication strength
note right: strength = coupling_strength
ImpGen -> ImpGen: Calculate implication confidence  
note right: confidence = min(agent_salience, arena_salience)

ImpGen -> AS: Create implication link
note right: Agent → Arena with (strength, confidence)

== Deduction Cycle ==
PLN -> AS: Find all implication links
AS -> PLN: Implication atoms

loop For each implication A→B
    PLN -> AS: Find atoms matching antecedent A
    AS -> PLN: Antecedent instances with truth values
    
    alt Antecedent strength > 0.7
        PLN -> Ded: Apply deduction rule
        Ded -> Ded: Calculate consequent truth value
        note right: TV(B) = TV(A→B) ⋅ TV(A)\nstrength = impl_strength ⋅ ant_strength\nconfidence = min(impl_conf, ant_conf)
        
        Ded -> AS: Update consequent truth value
        AS -> PLN: Confirm update
        PLN -> PLN: Record new conclusion
    end
end

== Abduction Cycle ==
loop For each implication A→B
    PLN -> AS: Find atoms matching consequent B
    AS -> PLN: Consequent instances with truth values
    
    alt Consequent strength > 0.7
        PLN -> Abd: Apply abduction rule
        Abd -> Abd: Calculate antecedent hypothesis
        note right: TV(A) = TV(B) ⋅ TV(A→B) ⋅ 0.8\nReduced confidence: 0.6 factor
        
        Abd -> AS: Update antecedent as hypothesis
        AS -> PLN: Confirm hypothesis
        PLN -> PLN: Record new hypothesis
    end
end

== Results Integration ==
PLN -> RR: Return inference results summary
RR -> RR: Integrate PLN feedback into RR dynamics

@enduml
```

## Scheme Interface Command Processing

```plantuml
@startuml Scheme-Command-Process
!theme plain
title Scheme Interface Command Processing

actor User
participant "Scheme REPL" as REPL
participant "Expression Parser" as Parser
participant "Command Router" as Router
participant "RR Interface" as RRInt
participant "AtomSpace Interface" as ASInt
participant "PLN Interface" as PLNInt

== Command Input ==
User -> REPL: Enter Scheme expression
REPL -> Parser: Parse expression string
Parser -> Parser: Tokenize and validate syntax

alt Valid Expression
    Parser -> Router: Parsed command structure
else Invalid Expression
    Parser -> REPL: Syntax error message
    REPL -> User: Display error
end

== Command Routing ==
Router -> Router: Identify command type

alt RR Query Commands
    Router -> RRInt: (list-rr-nodes)
    RRInt -> RRInt: Collect all RR nodes
    RRInt -> Router: Formatted node list
    
    Router -> RRInt: (get-salience node-ID)
    RRInt -> RRInt: Look up specific node
    RRInt -> Router: Node salience value
    
    Router -> RRInt: (get-system-relevance)
    RRInt -> RRInt: Compute average relevance gradient
    RRInt -> Router: System-wide relevance

else AtomSpace Query Commands
    Router -> ASInt: (list-atoms)
    ASInt -> ASInt: Iterate through atom registry
    ASInt -> Router: Formatted atom list
    
    Router -> ASInt: (find-atom "name")
    ASInt -> ASInt: Search atoms by name pattern
    ASInt -> Router: Matching atoms

else Update Commands
    Router -> RRInt: (update-salience node-ID value)
    RRInt -> RRInt: Validate node ID and value
    RRInt -> RRInt: Update node salience
    RRInt -> Router: Update confirmation

else Inference Commands
    Router -> PLNInt: (run-pln-inference)
    PLNInt -> PLNInt: Execute full inference cycle
    PLNInt -> Router: Inference results summary
    
    Router -> RRInt: (find-patterns)
    RRInt -> RRInt: Analyze RR emergence patterns
    RRInt -> Router: Detected patterns

else Unknown Command
    Router -> REPL: Unknown command error
end

== Response Formatting ==
Router -> REPL: Command result
REPL -> REPL: Format as Scheme-style output
REPL -> User: Display formatted result

@enduml
```

## Persistent Storage Process Flow

```plantuml
@startuml Persistent-Storage-Process
!theme plain
title Persistent Storage and Memory Consolidation

participant "User Request" as User
participant "Storage Manager" as Storage
participant "AtomSpace Serializer" as ASSerial
participant "RR Serializer" as RRSerial  
participant "JSON Writer" as JSON
participant "Memory Consolidator" as Consolidator
participant "File System" as FS

== Save Operation ==
User -> Storage: Request save to file
Storage -> ASSerial: Serialize AtomSpace
Storage -> RRSerial: Serialize RR hypergraph

== AtomSpace Serialization ==
ASSerial -> ASSerial: Iterate through atoms
loop For each atom
    ASSerial -> JSON: Write atom metadata
    note right: {"id": N, "type": T, "name": "X"}
    ASSerial -> JSON: Write truth values  
    note right: "strength": S, "confidence": C
    ASSerial -> JSON: Write outgoing links
    note right: "outgoing": [id1, id2, ...]
end
ASSerial -> JSON: Write next_atom_id
ASSerial -> Storage: AtomSpace JSON ready

== RR Hypergraph Serialization ==
RRSerial -> RRSerial: Iterate through RR nodes
loop For each RR node
    RRSerial -> JSON: Write node properties
    note right: id, type, aar_type, label
    RRSerial -> JSON: Write RR dynamics
    note right: salience, affordance_potential, affordance_realization
    RRSerial -> JSON: Write trialectic state
    note right: [x, y, z] vector
end

RRSerial -> RRSerial: Iterate through RR edges
loop For each RR edge  
    RRSerial -> JSON: Write edge properties
    note right: id, type, from_node, to_node, strength
end
RRSerial -> Storage: RR JSON ready

== Memory Consolidation ==
Storage -> Consolidator: Request memory optimization
Consolidator -> Consolidator: Analyze atom confidence levels

loop For each atom
    alt Confidence < threshold (0.3)
        Consolidator -> Consolidator: Mark for removal
        note right: Low-confidence atoms are pruned
    else Confidence >= threshold
        Consolidator -> Consolidator: Keep in active memory
    end
end

Consolidator -> Consolidator: Remove marked atoms
Consolidator -> Storage: Report consolidation results

== File Writing ==
Storage -> FS: Write AtomSpace JSON file
Storage -> FS: Write RR hypergraph JSON file
FS -> Storage: Confirm file creation
Storage -> User: Save operation complete

== Load Operation ==
User -> Storage: Request load from file
Storage -> FS: Read AtomSpace JSON file
Storage -> FS: Read RR hypergraph JSON file
FS -> Storage: Return file contents

Storage -> ASSerial: Deserialize AtomSpace
Storage -> RRSerial: Deserialize RR hypergraph

ASSerial -> ASSerial: Parse JSON and recreate atoms
RRSerial -> RRSerial: Parse JSON and recreate RR structures

Storage -> User: Load operation complete

@enduml
```

## Multi-Level Emergence Detection

```plantuml
@startuml Multi-Level-Emergence
!theme plain
title Multi-Level Emergence Detection Process

participant "Emergence Monitor" as Monitor
participant "Agent Tracker" as AgentTrack
participant "Arena Tracker" as ArenaTrack
participant "Coupling Analyzer" as Coupling
participant "Coherence Calculator" as Coherence
participant "Pattern Recognizer" as Pattern
participant "Emergent Relation Creator" as Creator

== Continuous Monitoring ==
loop System Evolution
    Monitor -> AgentTrack: Check all agent nodes
    
    AgentTrack -> AgentTrack: Scan agent salience levels
    loop For each agent
        alt Salience > 0.8
            AgentTrack -> Monitor: High-salience agent detected
            Monitor -> ArenaTrack: Find coupled arenas for agent
            
            ArenaTrack -> Coupling: Analyze agent-arena pairs
            loop For each arena
                Coupling -> Coupling: Compute coupling strength
                note right: strength = Σ(edge_weights) / edge_count
                
                alt Coupling > 0.8
                    Coupling -> Monitor: Strong coupling detected
                    Monitor -> Coherence: Calculate trialectic coherence
                    
                    Coherence -> Coherence: Measure state correlations
                    note right: coherence = Σ(state[i] * state[next]) / n
                    
                    alt Coherence > 0.6
                        Coherence -> Pattern: Emergent pattern candidate
                        Pattern -> Pattern: Validate emergence criteria
                        
                        Pattern -> Pattern: Check temporal consistency
                        Pattern -> Pattern: Verify cross-level interactions
                        
                        alt All criteria met
                            Pattern -> Creator: Create emergent relation
                            Creator -> Creator: Generate new relation node
                            note right: Type = EMERGENT, connects agent-arena
                            Creator -> Creator: Set emergent properties
                            note right: salience = (agent + arena) * 0.5\naffordance_realization = 1.0
                            Creator -> Monitor: Emergence event recorded
                        end
                    end
                end
            end
        end
    end
    
    Monitor -> Monitor: Update emergence statistics
    Monitor -> Monitor: Log system evolution metrics
end

@enduml
```

## Integration Test Flow

```plantuml
@startuml Integration-Test-Flow
!theme plain
title RR-RNN Integration Test Process

participant "Test Runner" as Test
participant "RR Enhanced Test" as RRTest
participant "Next Directions Test" as NDTest
participant "Demo REPL Test" as REPLTest
participant "Validation Engine" as Validator

== Test Initialization ==
Test -> Test: Setup test environment
Test -> RRTest: Initialize basic RR test
Test -> NDTest: Initialize comprehensive test
Test -> REPLTest: Initialize REPL demo test

== Basic RR Enhanced Test ==
Test -> RRTest: Run test_rr_enhanced
RRTest -> RRTest: Create RR hypergraph
RRTest -> RRTest: Add test membranes (agent, arena, environment)
RRTest -> RRTest: Create AtomSpace integration
RRTest -> RRTest: Run 50 simulation steps

loop 10-step intervals
    RRTest -> RRTest: Update RR dynamics
    RRTest -> RRTest: Sync with AtomSpace
    RRTest -> RRTest: Check for emergent patterns
    RRTest -> Validator: Validate state consistency
end

RRTest -> RRTest: Compute final system relevance
RRTest -> Test: Basic test results

== Comprehensive Next Directions Test ==
Test -> NDTest: Run test_next_directions
NDTest -> NDTest: Setup comprehensive environment

NDTest -> NDTest: Test PLN Integration
note right: Generate implications, run inference cycles
NDTest -> NDTest: Test Scheme Interface  
note right: Execute 8+ command types
NDTest -> NDTest: Test Persistent Storage
note right: Save/load, memory consolidation
NDTest -> NDTest: Test Multi-Level Integration
note right: Hierarchical structures, emergence detection

NDTest -> Validator: Validate all subsystem interactions
NDTest -> Test: Comprehensive test results

== REPL Demo Test ==
Test -> REPLTest: Run demo_repl
REPLTest -> REPLTest: Create test RR environment
REPLTest -> REPLTest: Start Scheme evaluator
REPLTest -> REPLTest: Execute demo command sequence

loop Demo commands
    REPLTest -> REPLTest: (list-rr-nodes)
    REPLTest -> REPLTest: (get-system-relevance)  
    REPLTest -> REPLTest: (find-patterns)
    REPLTest -> REPLTest: (get-salience node-1)
    REPLTest -> Validator: Validate command responses
end

REPLTest -> Test: REPL test results

== Final Validation ==
Test -> Validator: Aggregate all test results
Validator -> Validator: Check implementation completeness
note right: ✓ PLN Integration\n✓ Scheme Interface\n✓ Persistent Storage\n✓ Multi-Level Integration

Validator -> Validator: Verify system stability
Validator -> Validator: Confirm feature integration
Validator -> Test: Final validation report

Test -> Test: Generate test summary
note right: All Next Development Directions\nsuccessfully implemented and tested

@enduml
```

These PlantUML diagrams provide detailed process flows for all major components of the RR-RNN system, showing the intricate interactions between relevance realization dynamics, symbolic reasoning, and cognitive architecture integration.