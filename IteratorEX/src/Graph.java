import java.util.Iterator;

public class Graph implements Aggregate {
	private Point[] graph;
	private int last;

	public Graph(int size) {
		this.graph = new Point[size];
		this.last = 0;
	}

	public Point getPoint(int index) {
		return graph[index];
	}

	public int getLast() {
		return last;
	}

	public void insertPoint(Point point) {
		if (last < graph.length) {
			graph[last++] = point;
		} else
			System.out.println("그래프 꽉참");
	}

	@Override
	public Iterator<Point> iterator() {
		return new GraphIterator(this);
	}
}