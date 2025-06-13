# P-Lingua Usage and Examples

## Introduction

This document demonstrates the practical usage of P-Lingua through detailed examples, showing how the architectural components work together to process membrane computing models.

## Basic Workflow

```mermaid
graph LR
    A[Write P-Lingua Code] --> B[Parse with plingua]
    B --> C[Generate Binary Model]
    C --> D[Simulate with psim]
    D --> E[Analyze Results]
    
    subgraph "File Types"
        F[.pli - Source files]
        G[.psb - Binary models]
        H[.psc - Configurations]
        I[.cpp - Generated code]
    end
    
    A --> F
    C --> G
    D --> H
    B --> I
    
    style A fill:#e3f2fd
    style D fill:#f1f8e9
    style E fill:#e8f5e8
```

## Example 1: Simple Membrane System

### P-Lingua Source Code

```plingua
@model<transition>

def main() {
    // Define a simple membrane with objects
    @mu = [a{3}, b{2}]'1;
    
    // Evolution rules
    [a --> b]'1;
    [b --> c]'1;
    [c --> @d]'1;  // dissolution
}
```

### Parsing Process Flow

```mermaid
sequenceDiagram
    participant Source as P-Lingua Source
    participant Lexer as Lexical Analyzer
    participant Parser as Parser
    participant Semantic as Semantic Analyzer
    participant Model as P-System Model
    
    Source->>Lexer: @model<transition>...
    Lexer->>Parser: TOKEN_MODEL, TOKEN_IDENTIFIER...
    Parser->>Semantic: AST nodes
    Note over Semantic: Validates membrane structure
    Note over Semantic: Checks rule consistency
    Semantic->>Model: Validated P-System
    Model-->>Source: Success/Error
```

### Generated Internal Representation

```mermaid
graph TD
    subgraph "P-System Model"
        A[Model: transition]
        B[Initial Structure]
        C[Rules Set]
        D[Semantics]
    end
    
    subgraph "Membrane Structure"
        E[Membrane '1']
        F[Objects: a{3}, b{2}]
        G[Charge: neutral]
    end
    
    subgraph "Evolution Rules"
        H[Rule 1: a → b]
        I[Rule 2: b → c]
        J[Rule 3: c → @d]
    end
    
    A --> B
    A --> C
    A --> D
    
    B --> E
    E --> F
    E --> G
    
    C --> H
    C --> I
    C --> J
    
    style A fill:#e3f2fd
    style E fill:#f1f8e9
    style H fill:#fff3e0
```

## Example 2: Complex Membrane Division

### P-Lingua Source Code

```plingua
@model<transition>

def division_example() {
    // Membrane with division rules
    @mu = [a{5}, trigger]'1;
    
    // Division rule: one membrane becomes two
    [trigger [ ]'1 --> [result1]'1 [result2]'1];
    
    // Object evolution within membranes
    [a --> b]'1;
    [b --> c]'1;
}
```

### Division Process Visualization

```mermaid
stateDiagram-v2
    state "Initial Configuration" as Init {
        [*] --> Membrane1
        Membrane1 : Label: 1
        Membrane1 : Objects: a{5}, trigger
    }
    
    state "After Division" as Divided {
        [*] --> Membrane1_copy1
        [*] --> Membrane1_copy2
        Membrane1_copy1 : Label: 1
        Membrane1_copy1 : Objects: result1, a{5}
        Membrane1_copy2 : Label: 1
        Membrane1_copy2 : Objects: result2, a{5}
    }
    
    Init --> Divided : Division rule applied
    
    state "Evolution Continues" as Evolution {
        [*] --> Membrane1_evolved1
        [*] --> Membrane1_evolved2
        Membrane1_evolved1 : Objects: result1, b{n}, c{m}
        Membrane1_evolved2 : Objects: result2, b{p}, c{q}
    }
    
    Divided --> Evolution : Object evolution rules
```

### Simulation Step Details

```mermaid
sequenceDiagram
    participant Simulator
    participant RuleSelector
    participant Configuration
    participant Membrane1
    participant NewMembrane
    
    Simulator->>RuleSelector: Select applicable rules
    RuleSelector->>Configuration: Check current state
    Configuration->>Membrane1: Get membrane state
    Membrane1-->>Configuration: {trigger, a{5}}
    
    RuleSelector->>RuleSelector: Find division rule
    RuleSelector-->>Simulator: Division rule applicable
    
    Simulator->>Configuration: Apply division
    Configuration->>NewMembrane: Create new membrane
    Configuration->>Membrane1: Update original
    Configuration->>Configuration: Update parent references
    
    Note over Configuration: Membrane division complete
    Simulator->>Simulator: Continue with next step
```

## Example 3: Pattern Matching and Variables

### P-Lingua Source Code

```plingua
@model<transition>

def pattern_example(n) {
    // Parameterized membrane structure
    @mu = [ ]'1;
    @ms(1) += obj{i} : 1 <= i <= n;
    
    // Pattern-based rules with variables
    [obj{x}, obj{y} --> result{x+y}]'1 : x < y;
    [result{z} --> final{z}]'1 : z > 10;
}
```

### Pattern Resolution Process

```mermaid
flowchart TD
    A[Rule Pattern] --> B[Variable Extraction]
    B --> C[Constraint Analysis]
    C --> D[Object Matching]
    D --> E[Substitution]
    E --> F[Rule Instance]
    
    subgraph "Pattern Components"
        G[Variables: x, y, z]
        H[Constraints: x < y, z > 10]
        I[Objects: obj{x}, obj{y}]
        J[Products: result{x+y}]
    end
    
    B --> G
    C --> H
    D --> I
    E --> J
    
    style A fill:#e3f2fd
    style F fill:#e8f5e8
```

### Variable Binding Example

```mermaid
graph TB
    subgraph "Available Objects"
        A[obj{1}]
        B[obj{2}]
        C[obj{3}]
        D[obj{5}]
    end
    
    subgraph "Valid Bindings"
        E[x=1, y=2 → result{3}]
        F[x=1, y=3 → result{4}]
        G[x=1, y=5 → result{6}]
        H[x=2, y=3 → result{5}]
        I[x=2, y=5 → result{7}]
        J[x=3, y=5 → result{8}]
    end
    
    subgraph "Constraint Check"
        K[x < y: satisfied]
        L[Generate rule instances]
    end
    
    A --> E
    A --> F
    A --> G
    B --> H
    B --> I
    C --> J
    
    E --> K
    F --> K
    G --> K
    H --> K
    I --> K
    J --> K
    
    K --> L
    
    style A fill:#e3f2fd
    style E fill:#f1f8e9
    style K fill:#e8f5e8
```

## Example 4: Multi-Environment System

### P-Lingua Source Code

```plingua
@model<multienvironment>

def multi_env_system() {
    // Multiple environments with communication
    @mu = [ env1 ]'E1 [ env2 ]'E2;
    
    @ms(E1) += signal{1};
    @ms(E2) += receptor{1};
    
    // Cross-environment communication
    signal{x} [ ]'E1 <--> [ message{x} ]'E2;
    
    // Local evolution in each environment
    [receptor{y}, message{z} --> activated{y+z}]'E2;
}
```

### Multi-Environment Architecture

```mermaid
graph TB
    subgraph "Environment E1"
        A[signal{1}]
        B[Local Rules]
        C[Communication Port]
    end
    
    subgraph "Environment E2"
        D[receptor{1}]
        E[Local Rules]
        F[Communication Port]
    end
    
    subgraph "Communication Channel"
        G[Message Queue]
        H[Protocol Handler]
        I[Synchronization]
    end
    
    C <--> G
    F <--> G
    G --> H
    H --> I
    
    A --> B
    D --> E
    
    style A fill:#e3f2fd
    style D fill:#f1f8e9
    style G fill:#fff3e0
```

## Build and Execution Process

### Compilation Workflow

```mermaid
graph LR
    A[P-Lingua Source] --> B[plingua compiler]
    B --> C[Binary Model File]
    C --> D[psim simulator]
    D --> E[Results/Output]
    
    subgraph "Compiler Stages"
        F[Lexical Analysis]
        G[Syntax Analysis]
        H[Semantic Analysis]
        I[Code Generation]
    end
    
    subgraph "Simulator Stages"
        J[Model Loading]
        K[Initial Configuration]
        L[Rule Application]
        M[Termination Check]
    end
    
    B --> F
    F --> G
    G --> H
    H --> I
    
    D --> J
    J --> K
    K --> L
    L --> M
    
    style B fill:#e3f2fd
    style D fill:#f1f8e9
```

### Command Line Usage

```bash
# Compile P-Lingua source to binary model
./bin/plingua -i examples/graph.pli -o models/graph.psb

# Simulate the model
./bin/psim -i models/graph.psb -s 100 -v 2

# Generate C++ code
./bin/plingua -i examples/graph.pli -o generated/graph.cpp -f cpp
```

### Performance Monitoring

```mermaid
graph TD
    subgraph "Execution Metrics"
        A[Parse Time]
        B[Memory Usage]
        C[Rule Applications]
        D[Step Count]
    end
    
    subgraph "Performance Counters"
        E[Object Operations]
        F[Membrane Operations]
        G[Pattern Matches]
        H[Rule Conflicts]
    end
    
    subgraph "Output Formats"
        I[Console Stats]
        J[Log Files]
        K[CSV Reports]
        L[JSON Metrics]
    end
    
    A --> I
    B --> J
    C --> K
    D --> L
    
    E --> I
    F --> J
    G --> K
    H --> L
    
    style A fill:#e3f2fd
    style E fill:#f1f8e9
    style I fill:#e8f5e8
```

## Error Handling Examples

### Common Parsing Errors

```mermaid
graph LR
    subgraph "Syntax Errors"
        A[Missing Semicolon]
        B[Unmatched Brackets]
        C[Invalid Identifiers]
    end
    
    subgraph "Semantic Errors"
        D[Undefined Variables]
        E[Type Mismatches]
        F[Invalid Rule Patterns]
    end
    
    subgraph "Error Recovery"
        G[Error Location]
        H[Suggested Fixes]
        I[Continue Parsing]
    end
    
    A --> G
    B --> G
    C --> G
    D --> G
    E --> G
    F --> G
    
    G --> H
    H --> I
    
    style A fill:#ffebee
    style G fill:#fff3e0
    style I fill:#e8f5e8
```

### Runtime Error Handling

```mermaid
sequenceDiagram
    participant Simulator
    participant ErrorHandler
    participant Logger
    participant Recovery
    
    Simulator->>Simulator: Execute rule
    Note over Simulator: Division by zero detected
    
    Simulator->>ErrorHandler: Report error
    ErrorHandler->>Logger: Log error details
    ErrorHandler->>Recovery: Attempt recovery
    
    alt Recovery Successful
        Recovery-->>Simulator: Continue execution
    else Recovery Failed
        Recovery-->>Simulator: Terminate with error
    end
    
    Logger->>Logger: Write error report
```

## Integration Examples

### Using P-Lingua in C++ Applications

```cpp
#include <plingua/serialization.hpp>
#include <plingua/simulator.hpp>

int main() {
    // Load P-system model
    plingua::File file;
    loadFromFile("model.psb", file);
    
    // Create simulator
    plingua::simulator::Simulator sim;
    
    // Run simulation
    while (sim.ok()) {
        sim.step();
        
        // Access current configuration
        auto config = sim.getCurrentConfiguration();
        
        // Process results...
    }
    
    return 0;
}
```

### Integration Architecture

```mermaid
graph TB
    subgraph "Host Application"
        A[Main Program]
        B[P-Lingua Interface]
        C[Result Processor]
    end
    
    subgraph "P-Lingua Library"
        D[Parser API]
        E[Simulator API]
        F[Serialization API]
    end
    
    subgraph "External Tools"
        G[Visualization Tools]
        H[Analysis Tools]
        I[Debugging Tools]
    end
    
    A --> B
    B --> D
    B --> E
    B --> F
    B --> C
    
    C --> G
    C --> H
    C --> I
    
    style A fill:#e3f2fd
    style D fill:#f1f8e9
    style G fill:#fff3e0
```

This documentation demonstrates how P-Lingua's architecture supports various usage patterns, from simple membrane systems to complex multi-environment models with pattern matching and variable binding. The framework's design enables both interactive exploration and programmatic integration.