class SamsungPhone implements PhoneInterface {
	public void sendCall() {
		System.out.println("띠리리리링");
	}

	public void receiveCall() {
		System.out.println("전화가 왔습니다.");
	}

	public void flash() {
		System.out.println("전화기에 불이 켜졌습니다.");
	}
}