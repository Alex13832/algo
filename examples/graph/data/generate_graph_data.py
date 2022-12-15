#!/usr/bin/python
# alex011235
# https://github.com/alex011235/algorithm>Algorithm
# https://plotly.com/python/network-graphs/

import math as m
import sys

import networkx as nx
import pandas as pd
import plotly.graph_objects as go


def plot_graph(graph, edge_x, edge_y):
    """
    Plots the graph with plotly.
    :param graph: The graphs to plot.
    :param edge_x: Edges that are connected, x-coordinates.
    :param edge_y: Edges that are connected, y-coordinates.
    :return: nothing.
    """
    # The edges in the plot
    edge_trace = go.Scatter(
        x=edge_x, y=edge_y,
        line=dict(width=0.5, color='#888'),
        hoverinfo='none',
        mode='lines')

    node_x = []
    node_y = []
    for node in graph.nodes():
        x, y = graph.nodes[node]['pos']
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
    for node, adjacencies in enumerate(graph.adjacency()):
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


def generate_general_purpose_graph_data(nbr_nodes, radius, file_name, plot=0):
    """
    Generates data for general graphs.
    :param nbr_nodes: The number of nodes in the graph.
    :param radius: Distance threshold value.
    :param file_name: File name for data file.
    :param plot: Plots the graph if plot is 1
    https://networkx.org/documentation/networkx-1.10/reference/generated/networkx.generators.geometric.random_geometric_graph.html
    :return: nothing
    """
    graph = nx.random_geometric_graph(int(nbr_nodes), radius)

    node1 = []
    node2 = []
    weights = []
    x0_values = []
    y0_values = []
    x1_values = []
    y1_values = []
    # Create edges
    edge_x = []
    edge_y = []

    for edge in graph.edges():
        x0, y0 = graph.nodes[edge[0]]['pos']
        x1, y1 = graph.nodes[edge[1]]['pos']
        edge_x.append(x0)
        edge_x.append(x1)
        edge_x.append(None)
        edge_y.append(y0)
        edge_y.append(y1)
        edge_y.append(None)

        # To CSV file
        a, b = edge
        w = m.sqrt(m.pow(x1 - x0, 2) + m.pow(y1 - y0, 2))

        node1.append(a)
        node2.append(b)
        weights.append(w)
        x0_values.append(x0)
        y0_values.append(y0)
        x1_values.append(x1)
        y1_values.append(y1)

    df = pd.DataFrame()
    df['Node1'] = node1
    df['Node2'] = node2
    df['W'] = weights
    df['X0'] = x0_values
    df['Y0'] = y0_values
    df['X1'] = x1_values
    df['Y1'] = y1_values
    df.to_csv(file_name, index=False)

    if plot:
        plot_graph(graph, edge_x, edge_y)


def main(argv):
    # nn = nearest neighbor, radius 0.45
    # scc = strongly connected_components, radius -> 0.125
    # mst = minimum spanning tree, radius -> 0.3
    # sp = shortest path, radius -> 0.125

    nbr_nodes = int(argv[0])
    radius = 0.3
    file_name = "../plot/nn_network_in.csv"
    plot = 0

    if len(argv) > 1:
        radius = float(argv[1])
    if len(argv) > 2:
        plot = int(argv[2])

    generate_general_purpose_graph_data(nbr_nodes, radius, file_name, plot)


if __name__ == "__main__":
    main(sys.argv[1:])
