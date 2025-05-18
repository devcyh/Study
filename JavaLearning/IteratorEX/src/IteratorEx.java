import java.util.Iterator;

public class IteratorEx {
	public static void main(String[] args) {
		Graph graph = new Graph(5);
		graph.insertPoint(new Point(0, 1));
		graph.insertPoint(new Point(2, 3));
		graph.insertPoint(new Point(4, 5));
		graph.insertPoint(new Point(6, 7));
		graph.insertPoint(new Point(8, 9));
		graph.insertPoint(new Point(10, 11));

		Iterator<Point> it = graph.iterator();
		while (it.hasNext()) {
			System.out.println(it.next());
		}
	}
}