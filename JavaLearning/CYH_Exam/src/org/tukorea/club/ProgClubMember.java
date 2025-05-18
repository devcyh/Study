package org.tukorea.club;

public class ProgClubMember {
	private String name;
	private String studentId;
	private String department;
	private String language;
	private String gender;

	public ProgClubMember(String name, String studentId, String department, String language, String gender) {
		this.name = name;
		this.studentId = studentId;
		this.department = department;
		this.language = language;
		this.gender = gender;
	}

	@Override
	public String toString() {
		return "ProgClubMember [name=" + name + ", studentId=" + studentId + ", department=" + department
				+ ", language=" + language + ", gender=" + gender + "]";
	}
}