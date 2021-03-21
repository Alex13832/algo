#!/usr/bin/python
# alex011235
# https://github.com/alex011235/algorithm>Algorithm
# https://plotly.com/python/network-graphs/

import pandas as pd
import plotly.graph_objects as go

df_res = pd.read_csv('../testfiles/mbbox_out2.csv')

x_in = df_res['x']
y_in = df_res['y']
label = df_res['Label']

x1 = x_in[label == 1]
y1 = y_in[label == 1]
x2 = x_in[label == 2]
y2 = y_in[label == 2]

points = go.Scatter(x=x1, y=y1, mode='markers', hoverinfo='text',
                    marker=dict(showscale=False,
                                colorscale='sunset',
                                reversescale=True, color=label,
                                size=12, colorbar=dict(thickness=15, xanchor='left', titleside='right'),
                                line_width=1))

bbox = go.Scatter(x=x2, y=y2,
                  marker=dict(showscale=False,
                              colorscale='aggrnyl',
                              reversescale=True, color=label,
                              size=8, colorbar=dict(thickness=15, xanchor='left', titleside='right'),
                              line_width=1),
                  line=dict(color="#ff5500", width=2))

# Create figure

fig = go.Figure(data=[points, bbox],
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
