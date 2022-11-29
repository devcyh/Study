import java.util.Iterator;

public class GraphIterator implements Iterator<Point> {
	private Graph graph;
	private int idx;

	public GraphIterator(Graph graph) {
		this.graph = graph;
		this.idx = 0;
	}

	@Override
	public boolean hasNext() {
		return idx < graph.getLast();
	}

	@Override
	public Point next() {
		return graph.getPoint(idx++);
	}
}