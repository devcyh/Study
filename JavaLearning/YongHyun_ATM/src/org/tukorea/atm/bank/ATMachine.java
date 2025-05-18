package org.tukorea.atm.bank;

import org.tukorea.atm.helpdesk.CustomerSvc;
import org.tukorea.atm.util.Statistics;
import java.util.Random;

public class ATMachine {
	private Account[] accountArray; // 고객계좌배열 참조변수
	private int machineBalance; // ATM 잔고
	private int maxAccountNum; // 고객계좌 참조변수 배열크기
	private int currentAccountNum; // 개설된 고객계좌 수
	private String managerPassword; // 관리자 비밀번호
	private int index; // 참조할 배열 원소의 인덱스

	public static final int BASE_ACCOUNT_ID = 100; // 고객계좌 발급 시 최소 번호
	// 랜덤으로 계좌 번호 발급
	// 범위 : 100부터 (계좌 발급 시 개설가능한 최대 계좌 수 * 2) 번호까지 부여

	public ATMachine(int size, int balance, String password) { // 생성자
		maxAccountNum = size;
		machineBalance = balance;
		managerPassword = password;
		accountArray = new Account[maxAccountNum];
		currentAccountNum = 0;
	}

	public void createAccount(String accountName, String passwd) { // 계좌 개설
		if (currentAccountNum >= maxAccountNum) {
			System.out.println("고객계좌배열이 꽉찼습니다.");
			return;
		}
		Random random = new Random();
		int randId;
		boolean flag;
		do {
			randId = random.nextInt(maxAccountNum * 2 - BASE_ACCOUNT_ID + 1) + BASE_ACCOUNT_ID;
			flag = false;
			for (int i = 0; i < currentAccountNum; i++)
				if (randId == accountArray[i].getAccountId())
					flag = true;
		} while (flag);
		accountArray[currentAccountNum++] = new Account(randId, 0, accountName, passwd);
		System.out.println(accountName + "님 " + randId + "번 계좌번호가 정상적으로 개설되었습니다. 감사합니다.");
	}

	private boolean searchAccountId(int accountId) { // 입력한 accountId를 가진 배열 원소를 탐색
		for (int i = 0; i < currentAccountNum; i++) {
			if (accountId == accountArray[i].getAccountId()) {
				index = i; // 입력한 id와 일치하는 배열 원소의 인덱스를 저장
				return true;
			}
		}
		return false;
	}

	public boolean checkIdPwd(int accountId, String passwd) { // id, pw 체크
		boolean isTrue = searchAccountId(accountId);
		if (isTrue) {
			isTrue = accountArray[index].authenticate(accountId, passwd);
			if (!isTrue)
				System.out.println("잘못된 비밀번호입니다.");
		} else
			System.out.println("존재하지 않는 계좌입니다.");
		return isTrue;
	}

	public void checkMoney() { // 계좌 조회
		System.out.println("계좌 잔액 : " + accountArray[index].getBalance());
	}

	public void depositMoney(int money) { // 계좌 입금
		accountArray[index].deposit(money);
		machineBalance += money;
		System.out.println("입금 후 잔액: " + accountArray[index].getBalance());
	}

	public void widrawMoney(int money) { // 계좌 출금
		if (money <= accountArray[index].getBalance()) {
			accountArray[index].widraw(money);
			machineBalance -= money;
			System.out.println("출금 후 잔액: " + accountArray[index].getBalance());
		} else
			System.out.println("잔고가 부족합니다.");
	}

	public void transfer(int receiverId, int money) { // 계좌 이체
		int senderIdx = index;
		if (searchAccountId(receiverId)) {
			if (money <= accountArray[senderIdx].getBalance()) {
				accountArray[index].deposit(money);
				accountArray[senderIdx].widraw(money);
				System.out.println("현재 잔액: " + accountArray[senderIdx].getBalance());
				System.out.println("계좌 이체를 완료하였습니다.");
			} else
				System.out.println("잔고가 부족합니다.");
		} else
			System.out.println("이체 계좌를 다시 확인하세요.");
	}

	public void requestSvc(int accountId, String passwd, String newPasswd) { // 고객 센터 (비밀번호 변경)
		CustomerSvc svc = new CustomerSvc(accountArray, currentAccountNum);
		svc.updatePasswdReq(accountId, passwd, newPasswd);
	}

	public void managerMode(String adminPwd) { // 고객 관리
		if (!managerPassword.equals(adminPwd)) {
			System.out.println("잘못된 비밀번호입니다.");
			return;
		}
		if (currentAccountNum <= 0) {
			System.out.println("개설된 계좌가 없습니다.");
			return;
		}
		System.out.print("ATM 현금 잔고: ");
		System.out.println(machineBalance);
		System.out.print("고객 잔고 총액: ");
		System.out.println(Statistics.sum(accountArray, currentAccountNum));
		System.out.print("고객 잔고 평균: ");
		System.out.println(Statistics.average(accountArray, currentAccountNum));
		System.out.print("고객 잔고 최고: ");
		System.out.println(Statistics.max(accountArray, currentAccountNum));
		System.out.println("고객 계좌 현황(고객 잔고 내림 차순 정렬)");
		Statistics.sort(accountArray, currentAccountNum);
		for (int i = 0; i < currentAccountNum; i++)
			System.out.println(accountArray[i].getAccountName() + " " + accountArray[i].getAccountId() + " "
					+ accountArray[i].getBalance());
	}

	public void displayMenu() { // 메인 메뉴 표시
		System.out.println("--------------------");
		System.out.println("-   TUKOREA BANK   -");
		System.out.println("--------------------");
		System.out.println("1. 계좌 개설");
		System.out.println("2. 계좌 조회");
		System.out.println("3. 계좌 입금");
		System.out.println("4. 계좌 출금");
		System.out.println("5. 계좌 이체");
		System.out.println("7. 고객 센터");
		System.out.println("8. 고객 관리");
		System.out.println("9. 업무 종료");
	}
}