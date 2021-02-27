#!/usr/bin/python
# alex011235
# https://github.com/alex011235/algorithm>Algorithm
# https://plotly.com/python/network-graphs/

import pandas as pd
import plotly.graph_objects as go

df_in = pd.read_csv('testfiles/nn_data_in.csv')
df_res = pd.read_csv('testfiles/nn_data_out.csv');

edge_x = []
edge_y = []
node_x = []
node_y = []

edge_res_x = []
edge_res_y = []
node_res_x = []
node_res_y = []

for x0, y0, x1, y1 in zip(df_in['X0'], df_in['Y0'], df_in['X1'], df_in['Y1']):
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

for x, y in zip(df_res['X'], df_res['Y']):
    edge_res_x.append(x)
    edge_res_y.append(y)
    node_res_x.append(x)
    node_res_y.append(y)

# The edges in the plot
edge_trace = go.Scatter(
    x=edge_x, y=edge_y,
    line=dict(width=0.5, color='#888'),
    hoverinfo='none',
    mode='lines')

# THe nodes in the plot
node_trace = go.Scatter(x=node_x, y=node_y, mode='markers', hoverinfo='text',
                        marker=dict(showscale=False, colorscale='Picnic', reversescale=True, color=[], size=10,
                                    colorbar=dict(thickness=15, xanchor='left', titleside='right'), line_width=2))

edge_res_trace = go.Scatter(x=edge_res_x, y=edge_res_y, line=dict(width=3.5, color='#FF4969'), hoverinfo='none',
                            mode='lines')

node_res_trace = go.Scatter(x=node_res_x, y=node_res_y, mode='markers', hoverinfo='text',
                            marker=dict(showscale=False, colorscale='Picnic', reversescale=True, color="#FF4969",
                                        size=12, colorbar=dict(thickness=15, xanchor='left', titleside='right'),
                                        line_width=1))

# Create network graph

fig = go.Figure(data=[edge_trace, node_trace, edge_res_trace, node_res_trace],
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
