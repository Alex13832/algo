#!/usr/bin/python
# alex011235
# https://github.com/alex011235/algorithm>Algorithm
# https://plotly.com/python/network-graphs/

import sys

import networkx as nx
import pandas as pd
import plotly.graph_objects as go


def main(argv):
    # argv[0] is the number of points.
    graph = nx.random_geometric_graph(int(argv[0]), 0.125)

    node_x = []
    node_y = []
    for node in graph.nodes():
        x, y = graph.nodes[node]['pos']
        node_x.append(x)
        node_y.append(y)

    # Save data with Pandas
    df = pd.DataFrame()
    df['x'] = node_x
    df['y'] = node_y
    df.to_csv('testfiles/triangulate_in.csv', index=False)

    # THe nodes in the plot
    node_trace = go.Scatter(
        x=node_x, y=node_y,
        mode='markers',
        hoverinfo='text',
        marker=dict(
            showscale=False,
            colorscale='Picnic',
            reversescale=True,
            color=[],
            size=10,
            colorbar=dict(
                thickness=15,
                # title='Node Connections',
                xanchor='left',
                titleside='right'
            ),
            line_width=2))

    # Color Node Points

    node_adjacencies = []
    node_text = []
    for node, adjacencies in enumerate(graph.adjacency()):
        node_adjacencies.append(len(adjacencies[1]))
        node_text.append('# of connections: ' + str(len(adjacencies[1])))

    node_trace.marker.color = node_adjacencies
    node_trace.text = node_text

    # Create network graph

    fig = go.Figure(data=[node_trace],
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


if __name__ == "__main__":
    main(sys.argv[1:])
