#!/usr/bin/python
# alex011235
# https://github.com/alex011235/algorithm>Algorithm

import pandas as pd
import plotly.graph_objects as go

df_in = pd.read_csv("testfiles/mst_network_in.csv")
df_res = pd.read_csv("testfiles/mst_network_out.csv")

edge_x_in = []
edge_y_in = []
node_x_in = []
node_y_in = []

for x0, y0, x1, y1 in zip(df_in['X0'], df_in['Y0'], df_in['X1'], df_in['Y1']):
    edge_x_in.append(x0)
    edge_x_in.append(x1)
    edge_x_in.append(None)
    edge_y_in.append(y0)
    edge_y_in.append(y1)
    edge_y_in.append(None)
    node_x_in.append(x0)
    node_x_in.append(x1)
    node_y_in.append(y0)
    node_y_in.append(y1)

edge_x_res = []
edge_y_res = []
node_x_res = []
node_y_res = []

for x0, y0, x1, y1 in zip(df_res['X0'], df_res['Y0'], df_res['X1'], df_res['Y1']):
    edge_x_res.append(x0)
    edge_x_res.append(x1)
    edge_x_res.append(None)
    edge_y_res.append(y0)
    edge_y_res.append(y1)
    edge_y_res.append(None)
    node_x_res.append(x0)
    node_x_res.append(x1)
    node_y_res.append(y0)
    node_y_res.append(y1)

edge_trace_in = go.Scatter(x=edge_x_in, y=edge_y_in, line=dict(width=1.0, color='#AAA'), hoverinfo='none', mode='lines')

node_trace_in = go.Scatter(x=node_x_in, y=node_y_in, mode='markers', hoverinfo='text',
                           marker=dict(showscale=False, color="#FF4969", size=10,
                                       colorbar=dict(thickness=15, xanchor='left', titleside='right'), line_width=2))

edge_trace_res = go.Scatter(x=edge_x_res, y=edge_y_res, line=dict(width=3.5, color='#'), hoverinfo='none',
                            mode='lines')

node_trace_res = go.Scatter(x=node_x_res, y=node_y_res, mode='markers', hoverinfo='text',
                            marker=dict(showscale=False, color="#FF4969", size=10,
                                        colorbar=dict(thickness=15, xanchor='left', titleside='right'), line_width=2))

annotation_text = "Number of nodes: " + str(len(df_res) + 1) + ", MST weight: " + str(round(sum(
    df_res['W']), 2)) + ", of total: " + str(round(sum(df_in['W']), 2))

# Create network graph

fig = go.Figure(data=[edge_trace_in, node_trace_in, edge_trace_res, node_trace_res],
                layout=go.Layout(
                    title='',
                    titlefont_size=16,
                    showlegend=False,
                    hovermode='closest',
                    margin=dict(b=20, l=5, r=5, t=40),
                    annotations=[dict(
                        text=annotation_text,
                        showarrow=False,
                        xref="paper", yref="paper",
                        x=0.005, y=-0.002)],
                    xaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
                    yaxis=dict(showgrid=False, zeroline=False, showticklabels=False))
                )
fig.show()
