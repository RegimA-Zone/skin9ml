# Persona-Reservoir Parameter Mapping

This document provides a comprehensive explanation of how human-understandable personality traits and cognitive skills are mapped to technical parameters for the Deep Tree Echo State Network (DTESN) reservoir computing system.

## Overview

The Silicon Sage platform translates human personality characteristics into technical neural network parameters to create AI personas with distinct cognitive capabilities. This mapping is the core of the system's ability to generate different problem-solving approaches based on personality profiles.

## Core Personality Traits (Big Five)

The Big Five personality traits are mapped to fundamental reservoir parameters as follows:

| Personality Trait | Reservoir Parameter | Relationship |
|-------------------|---------------------|-------------|
| Openness          | Spectral Radius     | Higher openness = larger spectral radius, allowing more creative exploration of state space |
| Conscientiousness | Leak Rate           | Higher conscientiousness = higher leak rate, enabling more methodical memory retention |
| Extraversion      | Input Scaling       | Higher extraversion = stronger input scaling, increasing sensitivity to external inputs |
| Agreeableness     | Reservoir Density   | Higher agreeableness = denser connectivity, reflecting cooperative integration |
| Stability         | Ridge Regression    | Higher stability = lower ridge regression, requiring less regularization |

## Cognitive Skills

Cognitive skills are mapped to advanced reservoir parameters as follows:

| Cognitive Skill     | Reservoir Parameter(s)              | Relationship |
|---------------------|-------------------------------------|-------------|
| Reasoning           | Ridge Regression, Hyperedge Order   | Better reasoning = lower regularization needs, higher-order relationships |
| Memory              | Leak Rate, Temporal Horizon         | Better memory = finer temporal control, longer temporal context |
| Perception          | Input Scaling, Temporal Resolution  | Better perception = higher input sensitivity, finer temporal granularity |
| Planning            | Temporal Horizon, Evolution Steps   | Better planning = extended temporal horizon, more computation steps |
| Creativity          | Hypervertex Dimension, Dimensionality | Higher creativity = higher-dimensional representation spaces |
| Metacognition       | Attention Weights, Hypervertex Dimension | Better metacognition = stronger attention mechanisms, richer self-representations |
| Context Integration | Attention Weights, Reservoir Density | Better integration = stronger attention, denser connectivity |
| Recursion           | Recursion Depth                     | Better recursion = deeper recursive processing capabilities |

## Emotional Dimensions

Emotional dimensions affect neuroenergetic parameters:

| Emotional Dimension | Reservoir Parameter      | Relationship |
|---------------------|--------------------------|-------------|
| Valence             | -                        | Currently not directly mapped, but influences mood-based adjustments |
| Arousal             | Activation Cost          | Higher arousal = lower activation threshold (inverse relation) |
| Dominance           | Inhibition Strength      | Higher dominance = stronger inhibition of competing activations |
| Confidence          | -                        | Currently used for runtime adjustments rather than fixed parameters |
| Current Mood        | -                        | Used for dynamic adjustments during operation |

## P-System Configuration

The membrane computing (P-System) configuration is derived from multiple dimensions:

| P-System Parameter  | Source Dimensions                            | Relationship |
|---------------------|----------------------------------------------|-------------|
| Membrane Count      | Context Integration, Metacognition           | Better integration and metacognition = more nested membranes |
| Evolution Steps     | Planning, Reasoning                          | Better planning and reasoning = more computation steps |
| Attention Heads     | Perception, Context Integration              | Better perception and integration = more parallel attention |
| Dimensionality      | Creativity, Openness                         | Higher creativity and openness = higher-dimensional spaces |
| Parallelism         | Extraversion, Context Integration            | Higher extraversion and integration = more parallel processing |

## Technical Parameter Details

### Core Reservoir Parameters

1. **Spectral Radius** (0.5-1.0)
   - Controls the overall dynamics and stability of the reservoir
   - Affects how quickly perturbations grow or decay

2. **Leak Rate** (0.1-0.9)
   - Controls the memory decay rate in the reservoir
   - Higher values = faster forgetting of past states

3. **Input Scaling** (0.2-1.0)
   - Controls how strongly external inputs affect reservoir states
   - Higher values = stronger influence of inputs

4. **Reservoir Density** (0.1-0.6)
   - Controls connectivity density within the reservoir
   - Higher values = more interconnections between nodes

5. **Ridge Regression** (0.01-0.21)
   - Controls regularization during training
   - Higher values = more noise tolerance but less precision

### Advanced Temporal Parameters

6. **Time Scale** (0.1-1.0)
   - Controls temporal responsiveness of the reservoir
   - Higher values = finer temporal processing

7. **Temporal Horizon** (5-25)
   - Maximum temporal context window in steps
   - Higher values = longer memory of past states

8. **Temporal Resolution** (0.1-1.0)
   - Granularity of temporal processing
   - Higher values = more detailed temporal processing

### Attention and Recursion Parameters

9. **Attention Weights** (0.3-1.0)
   - Influence of attention mechanisms
   - Higher values = stronger selective focus

10. **Recursion Depth** (0.5-2.0)
    - Depth of recursive processing
    - Higher values = more nested recursive patterns

### Hypergraph Parameters

11. **Hyperedge Order** (2-5)
    - Maximum order of hyperedges (nodes per edge)
    - Higher values = more complex relationships

12. **Hypervertex Dimension** (8-40)
    - Dimensionality of node representations
    - Higher values = richer node representations

### Neuroenergetic Parameters

13. **Activation Cost** (0.2-1.0)
    - Energy threshold for node activation
    - Higher values = more energy needed for activation

14. **Inhibition Strength** (0.3-1.0)
    - Strength of inhibitory connections
    - Higher values = stronger suppression of competing activations

## Complex Interdependencies

Many parameters exhibit complex interdependencies. For example:

1. **Spectral Radius + Stability**: Both affect the overall stability of the network dynamics
2. **Memory + Metacognition**: Together determine how well the system can maintain and reflect on its internal state
3. **Creativity + Openness**: Jointly influence the exploration of novel solution spaces
4. **Reasoning + Stability**: Together influence how well the system handles noise and uncertainty

## Dynamic Adjustment

The mapping is not static but can be dynamically adjusted based on:

1. Current emotional state (mood)
2. Context of the task or problem
3. Feedback from performance metrics
4. Learning and adaptation over time

## Implementation Notes

The mapping is implemented in the `mapPersonaToReservoir` function in `/shared/reservoir-persona-mapping.ts`.

Parameter weights are carefully calibrated to ensure:
- Balanced influence of different personality dimensions
- Reasonable ranges for technical parameters
- Smooth transitions between different persona configurations
- Compatibility with the underlying DTESN implementation

## Future Directions

Future enhancements to the mapping system include:
- Learning-based adaptation of mapping weights
- More differentiated emotional influences
- Task-specific parameter optimization
- Integration of more advanced cognitive dimensions like analogical reasoning and counterfactual thinking