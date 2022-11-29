public class InheritanceEx {
	public static void main(String[] args) {
		Student s = new Student();
		s.set();

		System.out.print(s.getAge() + ", " + s.getName() + ", " + s.getHeight() + ", " + s.getWeight());
	}
}