#!/usr/bin/python
# alex011235
# https://github.com/alex011235/algorithm>Algorithm

import pandas as pd
import plotly.graph_objects as go

df = pd.read_csv('triangulate_out.csv')
x1 = df['x1']
y1 = df['y1']
x2 = df['x2']
y2 = df['y2']

# Create edges
edge_x = []
edge_y = []
node_x = []
node_y = []

for x_0, y_0, x_1, y_1 in zip(x1, y1, x2, y2):
    edge_x.append(x_0)
    edge_x.append(x_1)
    edge_x.append(None)
    edge_y.append(y_0)
    edge_y.append(y_1)
    edge_y.append(None)

    node_x.append(x_0)
    node_x.append(x_1)
    node_y.append(y_0)
    node_y.append(y_1)

edge_trace = go.Scatter(
    x=edge_x, y=edge_y,
    line=dict(width=1.5, color='#888'),
    hoverinfo='none',
    mode='lines')

node_trace = go.Scatter(
    x=node_x, y=node_y,
    mode='markers',
    hoverinfo='text',
    marker=dict(
        showscale=False,
        color="#44C1FF",
        size=10,
        colorbar=dict(
            thickness=15,
            xanchor='left',
            titleside='right'
        ),
        line_width=2)
)

# Create network graph

fig = go.Figure(data=[edge_trace, node_trace],
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
