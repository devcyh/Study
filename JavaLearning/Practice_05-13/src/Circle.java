class Circle implements Shape {
	private int radius;

	public Circle(int radius) {
		this.radius = radius;
	}

	public void draw() {
		System.out.println("반지름이 " + radius + "인 원입니다.");
	}

	public double getArea() {
		return PI * radius * radius;
	}
}