#!/usr/bin/python
# alex011235
# https://github.com/alex011235/algorithm>Algorithm
# https://plotly.com/python/network-graphs/

import pandas as pd
import plotly.graph_objects as go

df_res = pd.read_csv('closest_pair_out1.csv')

x_in = df_res['x']
y_in = df_res['y']
label = df_res['Label']
print(max(label))

nodes = go.Scatter(x=x_in, y=y_in, mode='markers', hoverinfo='text',
                   marker=dict(showscale=False,
                               colorscale='sunset',
                               reversescale=True, color=label,
                               size=12, colorbar=dict(thickness=15, xanchor='left', titleside='right'),
                               line_width=1))

# Create figure

fig = go.Figure(data=[nodes],
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
