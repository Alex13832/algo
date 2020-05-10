#!/usr/bin/python
# alex011235
# https://github.com/alex011235/algorithm>Algorithm
# https://plotly.com/python/network-graphs/

import math as m
import sys

import networkx as nx
import plotly.graph_objects as go


def main(argv):
    # argv[0] is the number of nodes.
    G = nx.random_geometric_graph(int(argv[0]), 0.125)

    # Open file and print header
    f = open("testfiles/mst_network_in.csv", "w")
    f.write("Node1,Node2,W,x0,y0,x1,y1\n")

    # Create edges
    edge_x = []
    edge_y = []
    lines = []

    for edge in G.edges():
        x0, y0 = G.nodes[edge[0]]['pos']
        x1, y1 = G.nodes[edge[1]]['pos']
        edge_x.append(x0)
        edge_x.append(x1)
        edge_x.append(None)
        edge_y.append(y0)
        edge_y.append(y1)
        edge_y.append(None)

        # To CSV file
        a, b = edge
        w = m.sqrt(m.pow(x1 - x0, 2) + m.pow(y1 - y0, 2))
        f.write(
            str(a) + ',' + str(b) + ',' + str(w) + ',' + str(x0) + ',' + str(y0) + ',' + str(x1) + ',' + str(y1) + '\n')

    f.close()

    # The edges in the plot
    edge_trace = go.Scatter(
        x=edge_x, y=edge_y,
        line=dict(width=0.5, color='#888'),
        hoverinfo='none',
        mode='lines')

    node_x = []
    node_y = []
    for node in G.nodes():
        x, y = G.nodes[node]['pos']
        node_x.append(x)
        node_y.append(y)

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
    for node, adjacencies in enumerate(G.adjacency()):
        node_adjacencies.append(len(adjacencies[1]))
        node_text.append('# of connections: ' + str(len(adjacencies[1])))

    node_trace.marker.color = node_adjacencies
    node_trace.text = node_text

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


if __name__ == "__main__":
    main(sys.argv[1:])
