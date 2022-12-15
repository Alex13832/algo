#!/usr/bin/python
# alex011235
# https://github.com/alex011235/algorithm>Algorithm
# https://plotly.com/python/network-graphs/

import pandas as pd
import plotly.graph_objects as go

df_res = pd.read_csv('dbscan_out1.csv')

x_in = df_res['x0']
y_in = df_res['x1']
cluster = df_res['label']
print(max(cluster))

nodes = go.Scatter(x=x_in, y=y_in, mode='markers', hoverinfo='text',
                   marker=dict(showscale=False,
                               colorscale='agsunset',
                               reversescale=True, color=cluster,
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

# ['aggrnyl', 'agsunset', 'algae', 'amp', 'armyrose', 'balance',
#  'blackbody', 'bluered', 'blues', 'blugrn', 'bluyl', 'brbg',
#  'brwnyl', 'bugn', 'bupu', 'burg', 'burgyl', 'cividis', 'curl',
#  'darkmint', 'deep', 'delta', 'dense', 'earth', 'edge', 'electric',
#  'emrld', 'fall', 'geyser', 'gnbu', 'gray', 'greens', 'greys',
#  'haline', 'hot', 'hsv', 'ice', 'icefire', 'inferno', 'jet',
#  'magenta', 'magma', 'matter', 'mint', 'mrybm', 'mygbm', 'oranges',
#  'orrd', 'oryel', 'peach', 'phase', 'picnic', 'pinkyl', 'piyg',
#  'plasma', 'plotly3', 'portland', 'prgn', 'pubu', 'pubugn', 'puor',
#  'purd', 'purp', 'purples', 'purpor', 'rainbow', 'rdbu', 'rdgy',
#  'rdpu', 'rdylbu', 'rdylgn', 'redor', 'reds', 'solar', 'spectral',
#  'speed', 'sunset', 'sunsetdark', 'teal', 'tealgrn', 'tealrose',
#  'tempo', 'temps', 'thermal', 'tropic', 'turbid', 'twilight',
#  'viridis', 'ylgn', 'ylgnbu', 'ylorbr', 'ylorrd'].
