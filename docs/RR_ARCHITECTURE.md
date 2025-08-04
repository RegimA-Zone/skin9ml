# RR-RNN Architecture Documentation

## Overview

The **RR-RNN (Relevance Realization with Recursive Neural Networks)** enhancement transforms traditional P-Lingua membrane computing into a sophisticated cognitive architecture platform by integrating:

1. **Relevance Realization (RR) Dynamics** - Dynamic self-organization through agent-arena-relation triads
2. **OpenCog AtomSpace Integration** - Symbolic knowledge representation and reasoning
3. **PLN (Probabilistic Logic Networks)** - Inference over uncertain knowledge
4. **Interactive Scheme Interface** - Real-time system exploration and manipulation

## Core RR Architecture

### Trialectic Co-Constitution Framework

```mermaid
graph TD
    subgraph "Trialectic Dynamics"
        A[Agent] --> |co-construction| B[Arena]
        B --> |co-construction| C[Relation]
        C --> |co-construction| A
    end
    
    subgraph "RR Properties"
        D[Salience]
        E[Affordance Potential]
        F[Affordance Realization]
        G[Trialectic State Vector]
    end
    
    subgraph "Mathematical Foundation"
        H[∀^ω(x ⇔^α y ⇔^α z ⇔^α x)]
        I[∇ℜ = lim_{t→∞} Σᵢ log(aᵣᵢ(t)/aₚᵢ(t))]
        J[agent ↔^δ arena ∈ ℝ^(∞×∞)]
    end
    
    A --> D
    B --> E
    C --> F
    A --> G
    
    D --> H
    E --> I
    F --> J
    
    style A fill:#e3f2fd
    style B fill:#f3e5f5
    style C fill:#e8f5e8
    style H fill:#fff3e0
```

### RR Hypergraph Structure

```mermaid
classDiagram
    class RRNode {
        +unsigned id
        +Type nodeType
        +AARType aarType
        +string label
        +double salience
        +double affordance_potential
        +double affordance_realization
        +vector~double~ trialectic_state
        +computeRelevanceGradient()
        +updateSalience(delta_time)
        +computeTrialecticCoherence()
    }
    
    class RREdge {
        +unsigned id
        +Type edgeType
        +unsigned from_node
        +unsigned to_node
        +double strength
        +double relevance_weight
        +updateCoConstruction(from, to, delta_time)
    }
    
    class RRHypergraph {
        +map~unsigned, RRNode~ nodes
        +map~unsigned, RREdge~ edges
        +set~unsigned~ agent_nodes
        +set~unsigned~ arena_nodes
        +set~unsigned~ relation_edges
        +updateRelevanceRealization(delta_time)
        +detectEmergentPatterns()
        +computeCouplingStrength(agent_id, arena_id)
    }
    
    class EmergentCluster {
        +unsigned agent_id
        +vector~unsigned~ arena_ids
        +vector~double~ coupling_strengths
        +double coherence
    }
    
    RRHypergraph --> RRNode
    RRHypergraph --> RREdge
    RRHypergraph --> EmergentCluster
    RRNode --> RREdge : connected by
```

## AtomSpace Integration Architecture

### RR-AtomSpace Bridge

```mermaid
graph LR
    subgraph "RR Hypergraph"
        A[RR Nodes]
        B[RR Edges]
        C[RR Properties]
    end
    
    subgraph "Bridge Layer"
        D[RRAtomSpaceIntegrator]
        E[Node Mapping]
        F[Property Sync]
        G[Pattern Detection]
    end
    
    subgraph "OpenCog AtomSpace"
        H[Concept Nodes]
        I[Evaluation Links]
        J[Inheritance Links]
        K[Truth Values]
    end
    
    A --> D
    B --> D
    C --> D
    
    D --> E
    D --> F
    D --> G
    
    E --> H
    F --> K
    G --> I
    G --> J
    
    style D fill:#e8f5e8
    style H fill:#f3e5f5
```

### Atom Structure Mapping

```mermaid
flowchart TD
    subgraph "RR Node Transformation"
        A[RR Node] --> B[Concept Node]
        A --> C[Truth Value: salience, affordance]
        A --> D[Inheritance: type, aar_type]
    end
    
    subgraph "RR Edge Transformation"
        E[RR Edge] --> F[Evaluation Link]
        E --> G[Predicate: 'relates']
        E --> H[Truth Value: strength, relevance]
    end
    
    subgraph "AtomSpace Structure"
        B --> I[Node Registry]
        C --> I
        D --> I
        F --> J[Link Registry]
        G --> J
        H --> J
    end
    
    I --> K[Pattern Matching]
    J --> K
    K --> L[Emergent Pattern Detection]
    
    style A fill:#e3f2fd
    style B fill:#f3e5f5
    style K fill:#e8f5e8
```

## PLN Integration Architecture

### PLN Truth Value System

```mermaid
graph TB
    subgraph "PLN Truth Values"
        A[Strength Component]
        B[Confidence Component]
        C[PLNTruthValue = (s, c)]
    end
    
    subgraph "PLN Operations"
        D[Negation: NOT(A) = (1-s, c)]
        E[Conjunction: AND(A,B) = (s_A * s_B, min(c_A, c_B))]
        F[Disjunction: OR(A,B) = (s_A + s_B - s_A*s_B, min(c_A, c_B))]
        G[Implication: A→B = (1-s_A+s_A*s_B, f(c_A,c_B))]
    end
    
    subgraph "Inference Rules"
        H[Deduction: A→B, A ⊢ B]
        I[Abduction: A→B, B ⊢ A]
        J[RR Pattern Implications]
    end
    
    A --> C
    B --> C
    C --> D
    C --> E
    C --> F
    C --> G
    
    D --> H
    E --> I
    F --> J
    G --> J
    
    style C fill:#e3f2fd
    style H fill:#f3e5f5
    style J fill:#e8f5e8
```

### PLN Inference Cycle

```mermaid
sequenceDiagram
    participant RR as RR Hypergraph
    participant PLN as PLN Engine
    participant AS as AtomSpace
    participant Impl as Implications
    
    RR->>PLN: High-coupling patterns
    PLN->>AS: Find agent-arena pairs
    AS-->>PLN: Coupled nodes
    PLN->>Impl: Generate implications
    Impl->>AS: Create implication links
    AS->>PLN: Start inference cycle
    
    loop Deduction
        PLN->>AS: Find A→B, A patterns
        AS-->>PLN: Matching patterns
        PLN->>AS: Apply deduction: infer B
    end
    
    loop Abduction
        PLN->>AS: Find A→B, B patterns
        AS-->>PLN: Matching patterns
        PLN->>AS: Apply abduction: hypothesize A
    end
    
    PLN-->>RR: Inference results
    RR->>RR: Update RR dynamics
```

## Scheme Interface Architecture

### REPL Command Processing

```mermaid
graph TD
    subgraph "User Interface"
        A[User Input]
        B[Command Parser]
        C[Expression Evaluator]
    end
    
    subgraph "Command Types"
        D[(list-rr-nodes)]
        E[(list-atoms)]
        F[(get-system-relevance)]
        G[(run-pln-inference)]
        H[(find-patterns)]
        I[(get-salience node-ID)]
        J[(update-salience node-ID VALUE)]
        K[(find-atom "NAME")]
    end
    
    subgraph "System Access"
        L[RR Hypergraph Access]
        M[AtomSpace Access]
        N[PLN Engine Access]
        O[Pattern Matcher]
    end
    
    A --> B
    B --> C
    C --> D
    C --> E
    C --> F
    C --> G
    C --> H
    C --> I
    C --> J
    C --> K
    
    D --> L
    E --> M
    F --> L
    G --> N
    H --> O
    I --> L
    J --> L
    K --> M
    
    style C fill:#e8f5e8
    style L fill:#f3e5f5
```

### Interactive Command Flow

```mermaid
stateDiagram-v2
    [*] --> REPL_Start
    REPL_Start --> Command_Input
    Command_Input --> Parse_Expression
    Parse_Expression --> Validate_Command
    
    Validate_Command --> Execute_Query: Read command
    Validate_Command --> Execute_Update: Write command
    Validate_Command --> Error_Handler: Invalid command
    
    Execute_Query --> Format_Response
    Execute_Update --> Update_System
    Update_System --> Format_Response
    Error_Handler --> Format_Response
    
    Format_Response --> Command_Input
    Command_Input --> [*]: quit/exit
    
    note right of Execute_Query
        Commands like:
        (list-rr-nodes)
        (get-system-relevance)
        (find-patterns)
    end note
    
    note right of Execute_Update
        Commands like:
        (update-salience node-ID VALUE)
        (run-pln-inference)
    end note
```

## Persistent Storage Architecture

### Serialization Framework

```mermaid
graph LR
    subgraph "In-Memory Structures"
        A[RR Hypergraph]
        B[AtomSpace]
        C[PLN State]
    end
    
    subgraph "Serialization Layer"
        D[JSON Serializer]
        E[RR Serializer]
        F[AtomSpace Serializer]
        G[Consolidator]
    end
    
    subgraph "Persistent Storage"
        H[RR JSON File]
        I[AtomSpace JSON File]
        J[Merged Knowledge Base]
    end
    
    A --> E
    B --> F
    C --> D
    
    E --> H
    F --> I
    D --> G
    
    G --> J
    H --> J
    I --> J
    
    style D fill:#e8f5e8
    style J fill:#f3e5f5
```

### Memory Consolidation Process

```mermaid
flowchart TD
    A[Current AtomSpace] --> B[Confidence Analysis]
    B --> C{Confidence > Threshold?}
    C -->|Yes| D[Keep Atom]
    C -->|No| E[Mark for Removal]
    
    D --> F[Active Memory]
    E --> G[Cleanup Queue]
    
    F --> H[Incremental Learning]
    G --> I[Memory Optimization]
    
    H --> J[Merge New Experiences]
    I --> K[Free Memory]
    
    J --> L[Updated Knowledge Base]
    K --> L
    
    style B fill:#e3f2fd
    style L fill:#e8f5e8
```

## Multi-Level Integration Architecture

### Hierarchical Membrane Structure

```mermaid
graph TB
    subgraph "Level 0: Environment"
        A[Global Environment]
    end
    
    subgraph "Level 1: Outer Membranes"
        B[Outer Agent 1]
        C[Outer Arena 1]
        D[Outer Agent 2]
        E[Outer Arena 2]
    end
    
    subgraph "Level 2: Inner Membranes"
        F[Inner Agent 1.1]
        G[Inner Arena 1.1]
        H[Inner Agent 1.2]
        I[Inner Arena 1.2]
    end
    
    subgraph "Cross-Level Dynamics"
        J[Emergence Detection]
        K[Coherence Propagation]
        L[Temporal Reasoning]
    end
    
    A --> B
    A --> C
    A --> D
    A --> E
    
    B --> F
    B --> G
    C --> H
    C --> I
    
    F --> J
    G --> J
    H --> K
    I --> K
    
    J --> L
    K --> L
    
    style A fill:#e3f2fd
    style J fill:#e8f5e8
```

### Emergence Detection Algorithm

```mermaid
flowchart TD
    A[Monitor Agent Salience] --> B{Salience > 0.8?}
    B -->|Yes| C[Check Arena Coupling]
    B -->|No| A
    
    C --> D{Coupling > 0.8?}
    D -->|Yes| E[Measure Trialectic Coherence]
    D -->|No| A
    
    E --> F{Coherence > 0.6?}
    F -->|Yes| G[Detect Cross-Level Pattern]
    F -->|No| A
    
    G --> H[Create Emergent Relation]
    H --> I[Update Multi-Level State]
    I --> J[Record Emergence Event]
    J --> A
    
    style G fill:#e8f5e8
    style H fill:#f3e5f5
```

## System Integration Flow

### Complete RR-RNN Processing Pipeline

```mermaid
sequenceDiagram
    participant User
    participant Parser as P-Lingua Parser
    participant RR as RR Engine
    participant AS as AtomSpace
    participant PLN as PLN Engine
    participant Scheme as Scheme REPL
    participant Storage as Persistent Storage
    
    User->>Parser: Load .pli file
    Parser->>RR: Create RR hypergraph
    RR->>AS: Initialize AtomSpace
    AS->>PLN: Setup inference engine
    
    User->>Scheme: Start interactive session
    
    loop RR Dynamics
        RR->>RR: Update trialectic states
        RR->>AS: Sync node properties
        AS->>PLN: Generate implications
        PLN->>PLN: Perform inference cycle
        PLN->>AS: Update truth values
        AS->>RR: Feedback updates
    end
    
    User->>Scheme: Execute commands
    Scheme->>RR: Query/update RR state
    Scheme->>AS: Query/update atoms
    Scheme->>PLN: Trigger inference
    Scheme-->>User: Return results
    
    User->>Storage: Save system state
    Storage->>AS: Serialize AtomSpace
    Storage->>RR: Serialize RR hypergraph
    Storage-->>User: Confirm save
```

## Performance Characteristics

### Computational Complexity Analysis

```mermaid
graph LR
    subgraph "RR Operations"
        A[Node Update: O(n)]
        B[Edge Update: O(e)]
        C[Emergence Detection: O(n²)]
        D[Trialectic Dynamics: O(n)]
    end
    
    subgraph "AtomSpace Operations"
        E[Node Sync: O(n)]
        F[Pattern Matching: O(a log a)]
        G[Truth Value Update: O(a)]
        H[Link Creation: O(l)]
    end
    
    subgraph "PLN Operations"
        I[Deduction: O(r·a)]
        J[Abduction: O(r·a)]
        K[Implication Generation: O(n²)]
        L[Inference Cycle: O(r·a·c)]
    end
    
    subgraph "Overall Complexity"
        M[Per Step: O(n² + r·a·c)]
        N[Memory: O(n + a + r)]
        O[Storage: O(n + a)]
    end
    
    A --> M
    E --> M
    I --> M
    
    A --> N
    E --> N
    
    E --> O
    A --> O
    
    style M fill:#ffebee
    style N fill:#f3e5f5
    style O fill:#e8f5e8
```

Where:
- `n` = number of RR nodes
- `e` = number of RR edges  
- `a` = number of atoms
- `r` = number of inference rules
- `l` = number of links
- `c` = inference cycles

This architecture documentation provides a comprehensive view of how RR-RNN enhances traditional membrane computing with cognitive capabilities, creating a sophisticated platform for symbolic-subsymbolic integration and emergent pattern recognition.