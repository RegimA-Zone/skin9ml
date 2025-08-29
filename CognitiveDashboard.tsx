import React, { useState, useEffect } from 'react';
import {
  Box,
  Grid,
  Card,
  CardContent,
  Typography,
  Button,
  Tabs,
  Tab,
  Paper,
  Chip,
  List,
  ListItem,
  ListItemText,
  ListItemIcon,
  Divider,
} from '@mui/material';
import {
  Psychology,
  Memory,
  Timeline,
  Lightbulb,
  Settings,
  Visibility,
  TrendingUp,
  Hub,
  AutoFixHigh,
  Refresh,
} from '@mui/icons-material';
import { LineChart, Line, XAxis, YAxis, CartesianGrid, Tooltip, ResponsiveContainer, 
         ScatterChart, Scatter, NetworkChart } from 'recharts';
import { useWebSocket } from '../hooks/useWebSocket';

interface CognitiveState {
  important_concepts: Array<{
    id: number;
    name: string;
    type: number;
    attention: number;
    truth_strength: number;
    truth_confidence: number;
  }>;
  patterns: Array<{
    id: number;
    type: number;
    strength: number;
    connections: Array<{
      id: number;
      name: string;
    }>;
  }>;
  reasoning_chains: string[];
  metrics: {
    attention_coherence: number;
    knowledge_integration: number;
    total_concepts: number;
    total_patterns: number;
  };
}

const CognitiveDashboard: React.FC = () => {
  const { wsService, isConnected } = useWebSocket();
  const [tabValue, setTabValue] = useState(0);
  const [cognitiveState, setCognitiveState] = useState<CognitiveState | null>(null);
  const [attentionViz, setAttentionViz] = useState<any>(null);
  const [trainingAnalysis, setTrainingAnalysis] = useState<any>(null);
  const [hyperparamRecommendations, setHyperparamRecommendations] = useState<any>(null);
  const [cognitiveMetrics, setCognitiveMetrics] = useState<any>(null);

  useEffect(() => {
    if (isConnected) {
      fetchCognitiveData();
      const interval = setInterval(fetchCognitiveData, 2000);
      return () => clearInterval(interval);
    }
  }, [isConnected]);

  const fetchCognitiveData = () => {
    if (wsService && isConnected) {
      wsService.send({ action: 'get_cognitive_state' });
      wsService.send({ action: 'get_attention_visualization' });
      wsService.send({ action: 'get_training_analysis' });
      wsService.send({ action: 'get_hyperparameter_recommendations' });
      wsService.send({ action: 'get_cognitive_metrics' });
    }
  };

  useEffect(() => {
    if (wsService) {
      wsService.on('cognitive_state', (data: any) => {
        setCognitiveState(data.data);
      });
      
      wsService.on('attention_visualization', (data: any) => {
        setAttentionViz(data.data);
      });
      
      wsService.on('training_analysis', (data: any) => {
        setTrainingAnalysis(data.data);
      });
      
      wsService.on('hyperparameter_recommendations', (data: any) => {
        setHyperparamRecommendations(data.data);
      });
      
      wsService.on('cognitive_metrics', (data: any) => {
        setCognitiveMetrics(data.data);
      });
    }
  }, [wsService]);

  const MetricCard: React.FC<{ title: string; value: string; icon: React.ReactNode; color: string }> = 
    ({ title, value, icon, color }) => (
    <Card sx={{ height: '100%' }}>
      <CardContent>
        <Box sx={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center', mb: 2 }}>
          <Typography variant="h6" color="text.secondary">
            {title}
          </Typography>
          <Box sx={{ color: color }}>
            {icon}
          </Box>
        </Box>
        <Typography variant="h3" component="div" sx={{ fontWeight: 700 }}>
          {value}
        </Typography>
      </CardContent>
    </Card>
  );

  const AttentionVisualization = () => (
    <Card sx={{ p: 3, height: 400 }}>
      <Typography variant="h6" gutterBottom sx={{ display: 'flex', alignItems: 'center', gap: 1 }}>
        <Hub /> Attention Network
      </Typography>
      <Box sx={{ 
        height: 300, 
        backgroundColor: 'rgba(0, 0, 0, 0.1)', 
        borderRadius: 2,
        display: 'flex',
        alignItems: 'center',
        justifyContent: 'center',
        position: 'relative'
      }}>
        {attentionViz && attentionViz.nodes ? (
          <Box sx={{ width: '100%', height: '100%', position: 'relative' }}>
            {attentionViz.nodes.map((node: any, index: number) => (
              <Box
                key={node.id}
                sx={{
                  position: 'absolute',
                  left: `${20 + (index % 5) * 15}%`,
                  top: `${20 + Math.floor(index / 5) * 20}%`,
                  width: `${Math.min(60, node.size || 30)}px`,
                  height: `${Math.min(60, node.size || 30)}px`,
                  borderRadius: '50%',
                  backgroundColor: node.color || '#00d4ff',
                  display: 'flex',
                  alignItems: 'center',
                  justifyContent: 'center',
                  color: 'white',
                  fontSize: '10px',
                  fontWeight: 'bold',
                  opacity: 0.8,
                  transition: 'all 0.3s ease',
                  '&:hover': {
                    opacity: 1,
                    transform: 'scale(1.1)',
                  }
                }}
                title={node.name}
              >
                {node.name?.substring(0, 3)}
              </Box>
            ))}
          </Box>
        ) : (
          <Typography variant="body2" color="text.secondary">
            🧠 Cognitive network initializing...
          </Typography>
        )}
      </Box>
    </Card>
  );

  const ConceptsList = () => (
    <Card sx={{ p: 2, height: 400 }}>
      <Typography variant="h6" gutterBottom sx={{ display: 'flex', alignItems: 'center', gap: 1 }}>
        <Psychology /> Active Concepts
      </Typography>
      <List sx={{ maxHeight: 300, overflow: 'auto' }}>
        {cognitiveState?.important_concepts?.slice(0, 10).map((concept) => (
          <ListItem key={concept.id}>
            <ListItemIcon>
              <Lightbulb sx={{ color: '#00d4ff' }} />
            </ListItemIcon>
            <ListItemText
              primary={concept.name}
              secondary={
                <Box sx={{ display: 'flex', gap: 1, mt: 1 }}>
                  <Chip
                    size="small"
                    label={`Attention: ${concept.attention.toFixed(3)}`}
                    color="primary"
                  />
                  <Chip
                    size="small"
                    label={`Truth: ${concept.truth_strength.toFixed(2)}`}
                    color="secondary"
                  />
                </Box>
              }
            />
          </ListItem>
        ))}
      </List>
    </Card>
  );

  const ReasoningChains = () => (
    <Card sx={{ p: 2, height: 400 }}>
      <Typography variant="h6" gutterBottom sx={{ display: 'flex', alignItems: 'center', gap: 1 }}>
        <Timeline /> Reasoning Chains
      </Typography>
      <Box sx={{ maxHeight: 300, overflow: 'auto' }}>
        {cognitiveState?.reasoning_chains?.map((chain, index) => (
          <Paper key={index} sx={{ p: 2, mb: 1, backgroundColor: 'rgba(0, 212, 255, 0.05)' }}>
            <Typography variant="body2" sx={{ fontFamily: 'monospace', whiteSpace: 'pre-line' }}>
              {chain}
            </Typography>
          </Paper>
        ))}
      </Box>
    </Card>
  );

  const HyperparameterRecommendations = () => (
    <Card sx={{ p: 2 }}>
      <Typography variant="h6" gutterBottom sx={{ display: 'flex', alignItems: 'center', gap: 1 }}>
        <AutoFixHigh /> AI Recommendations
      </Typography>
      {hyperparamRecommendations && (
        <List>
          {Object.entries(hyperparamRecommendations).map(([param, data]: [string, any]) => (
            <ListItem key={param}>
              <ListItemText
                primary={param.replace('_', ' ').toUpperCase()}
                secondary={
                  <Box>
                    <Typography variant="body2">
                      Current: {data.current} → Recommended: {data.recommended}
                    </Typography>
                    <Typography variant="caption" color="text.secondary">
                      {data.reason}
                    </Typography>
                  </Box>
                }
              />
            </ListItem>
          ))}
        </List>
      )}
    </Card>
  );

  const CognitiveMetricsChart = () => (
    <Card sx={{ p: 2, height: 400 }}>
      <Typography variant="h6" gutterBottom sx={{ display: 'flex', alignItems: 'center', gap: 1 }}>
        <TrendingUp /> Cognitive Evolution
      </Typography>
      <ResponsiveContainer width="100%" height="90%">
        <LineChart data={cognitiveMetrics?.attention_distribution || []}>
          <CartesianGrid strokeDasharray="3 3" stroke="rgba(255,255,255,0.1)" />
          <XAxis dataKey="concept" stroke="rgba(255,255,255,0.7)" />
          <YAxis stroke="rgba(255,255,255,0.7)" />
          <Tooltip 
            contentStyle={{ 
              backgroundColor: 'rgba(26, 26, 26, 0.9)', 
              border: '1px solid rgba(255,255,255,0.1)',
              borderRadius: '8px',
            }}
          />
          <Line 
            type="monotone" 
            dataKey="attention" 
            stroke="#00d4ff" 
            strokeWidth={2}
            dot={{ fill: '#00d4ff', strokeWidth: 2 }}
          />
        </LineChart>
      </ResponsiveContainer>
    </Card>
  );

  return (
    <Box sx={{ p: 3 }}>
      <Box sx={{ mb: 4 }}>
        <Typography variant="h1" gutterBottom sx={{ display: 'flex', alignItems: 'center', gap: 2 }}>
          <Psychology sx={{ fontSize: '2.5rem' }} />
          Cognitive AI Dashboard
        </Typography>
        <Typography variant="h6" color="text.secondary">
          🧠 OpenCog-inspired cognitive architecture with attention allocation and reasoning
        </Typography>
      </Box>

      {!isConnected && (
        <Box sx={{ mb: 2 }}>
          <Typography variant="body2" color="warning" sx={{ 
            textAlign: 'center', 
            p: 2, 
            backgroundColor: 'rgba(255, 152, 0, 0.1)', 
            borderRadius: 2,
            border: '1px solid rgba(255, 152, 0, 0.3)'
          }}>
            🔌 Connecting to cognitive backend... Make sure the API server is running!
          </Typography>
        </Box>
      )}

      <Box sx={{ mb: 3, display: 'flex', justifyContent: 'space-between', alignItems: 'center' }}>
        <Tabs value={tabValue} onChange={(_, newValue) => setTabValue(newValue)}>
          <Tab label="Overview" />
          <Tab label="Attention Network" />
          <Tab label="Reasoning" />
          <Tab label="Recommendations" />
        </Tabs>
        <Button 
          variant="outlined" 
          startIcon={<Refresh />}
          onClick={fetchCognitiveData}
          disabled={!isConnected}
        >
          Refresh
        </Button>
      </Box>