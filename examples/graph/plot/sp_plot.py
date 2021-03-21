#!/usr/bin/python
# alex011235
# https://github.com/alex011235/algorithm>Algorithm
# https://plotly.com/python/network-graphs/

import pandas as pd
import plotly.graph_objects as go

df_in = pd.read_csv('testfiles/shortest_path_data_in.csv')
df_res = pd.read_csv('testfiles/shortest_path_data_out.csv');

edges_x0 = df_in['X0']
edges_y0 = df_in['Y0']
edges_x1 = df_in['X1']
edges_y1 = df_in['Y1']
res_x = df_res['X']
res_y = df_res['Y']

edge_x = []
edge_y = []
node_x = []
node_y = []

edge_res_x = []
edge_res_y = []
node_res_x = []
node_res_y = []

for x0, y0, x1, y1 in zip(edges_x0, edges_y0, edges_x1, edges_y1):
    edge_x.append(x0)
    edge_x.append(x1)
    edge_x.append(None)
    edge_y.append(y0)
    edge_y.append(y1)
    edge_y.append(None)
    node_x.append(x0)
    node_x.append(x1)
    node_y.append(y0)
    node_y.append(y1)

for x, y in zip(res_x, res_y):
    edge_res_x.append(x)
    edge_res_y.append(y)
    node_res_x.append(x)
    node_res_y.append(y)

# The edges in the plot
edge_trace_in = go.Scatter(x=edge_x, y=edge_y, line=dict(width=0.5, color='#888'), hoverinfo='none', mode='lines')

# THe nodes in the plot
node_trace_in = go.Scatter(x=node_x, y=node_y, mode='markers', hoverinfo='text',
                           marker=dict(showscale=False, colorscale='Picnic', reversescale=True, color=[], size=10,
                                       colorbar=dict(thickness=15, xanchor='left', titleside='right'),
                                       line_width=2))

edge_trace_res = go.Scatter(x=edge_res_x, y=edge_res_y, line=dict(width=3.5, color='#FF4969'), hoverinfo='none',
                            mode='lines')

node_trace_res = go.Scatter(x=node_res_x, y=node_res_y, mode='markers', hoverinfo='text',
                            marker=dict(showscale=False, colorscale='Picnic', reversescale=True, color="#FF4969",
                                        size=12, colorbar=dict(thickness=15, xanchor='left', titleside='right'),
                                        line_width=1))

# Create network graph

fig = go.Figure(data=[edge_trace_in, node_trace_in, edge_trace_res, node_trace_res],
                layout=go.Layout(
                    title='',
                    titlefont_size=16,
                    showlegend=False,
                    hovermode='closest',
                    margin=dict(b=20, l=5, r=5, t=40),
                    annotations=[dict(
                        text="",
                        showarrow=False,
                        xref="paper", yref="paper",
                        x=0.005, y=-0.002)],
                    xaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
                    yaxis=dict(showgrid=False, zeroline=False, showticklabels=False))
                )

fig.show()
