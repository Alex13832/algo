import plotly.graph_objects as go

# Create edges

edge_x = []
edge_y = []
node_x = []
node_y = []

with open("../../../cmake-build-debug/examples/graph/testfiles/mst_network_out.csv") as file_in:
    lines = []
    flag_read_header = False

    for line in file_in:
        if flag_read_header:
            line = line[:-2]
            content = line.split(',')
            node1 = int(content[0])
            node2 = int(content[1])
            w = float(content[2])
            x0 = float(content[3])
            y0 = float(content[4])
            x1 = float(content[5])
            y1 = float(content[6])

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

        flag_read_header = True

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
