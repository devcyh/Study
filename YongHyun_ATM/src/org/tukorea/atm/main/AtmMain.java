package org.tukorea.atm.main;

import org.tukorea.atm.bank.ATMachine;
import java.util.InputMismatchException;
import java.util.Scanner;

public class AtmMain {
	public static void main(String[] args) {
		// 초기 설정 - 개설가능한 최대계좌수(1000계좌),
		// ATM 잔금(50만원), 관리자 암호
		ATMachine atm = new ATMachine(1000, 500000, "admin");

		Scanner scan = new Scanner(System.in);
		boolean flag = true;
		while (flag) {
			atm.displayMenu();
			System.out.print("메뉴를 선택하세요 >>");
			try {
				String accountName;
				String passwd;
				String newPasswd;
				int accountId;
				int money;
				int select = scan.nextInt();
				switch (select) {
				case 1: // 계좌 개설
					System.out.println("--------개설---------");
					System.out.print("이름 입력: ");
					accountName = scan.next();
					System.out.print("비밀번호 입력: ");
					passwd = scan.next();
					atm.createAccount(accountName, passwd);
					break;

				case 2: // 계좌 조회
					System.out.println("--------조회---------");
					System.out.print("계좌번호 입력: ");
					accountId = scan.nextInt();
					System.out.print("비밀번호 입력: ");
					passwd = scan.next();
					if (atm.checkIdPwd(accountId, passwd))
						atm.checkMoney();
					break;

				case 3: // 계좌 입금
					System.out.println("--------입금---------");
					System.out.print("계좌번호 입력: ");
					accountId = scan.nextInt();
					System.out.print("비밀번호 입력: ");
					passwd = scan.next();
					if (atm.checkIdPwd(accountId, passwd)) {
						System.out.print("입금액 입력: ");
						money = scan.nextInt();
						atm.depositMoney(money);
					}
					break;

				case 4: // 계좌 출금
					System.out.println("--------출금---------");
					System.out.print("계좌번호 입력: ");
					accountId = scan.nextInt();
					System.out.print("비밀번호 입력: ");
					passwd = scan.next();
					if (atm.checkIdPwd(accountId, passwd)) {
						System.out.print("출금액 입력: ");
						money = scan.nextInt();
						atm.widrawMoney(money);
					}
					break;

				case 5: // 계좌 이체
					System.out.println("--------이체---------");
					System.out.print("계좌번호 입력: ");
					accountId = scan.nextInt();
					System.out.print("비밀번호 입력: ");
					passwd = scan.next();
					if (atm.checkIdPwd(accountId, passwd)) {
						System.out.print("이체계좌 입력: ");
						accountId = scan.nextInt();
						System.out.print("이체금액 입력: ");
						money = scan.nextInt();
						atm.transfer(accountId, money);
					}
					break;

				case 7: // 고객 센터 (비밀번호 변경)
					System.out.println("-------암호변경--------");
					System.out.print("계좌번호 입력: ");
					accountId = scan.nextInt();
					System.out.print("기존 비밀번호 입력: ");
					passwd = scan.next();
					System.out.print("신규 비밀번호 입력: ");
					newPasswd = scan.next();
					atm.requestSvc(accountId, passwd, newPasswd);
					break;

				case 8: // 고객 관리
					System.out.println("-------고객관리--------");
					System.out.print("관리자 비밀번호 입력: ");
					passwd = scan.next();
					atm.managerMode(passwd);
					break;

				case 9: // 업무 종료
					System.out.print("안녕히 가세요 !");
					flag = false;
					break;

				default:
					System.out.println("정확한 숫자를 입력해주세요.");
					break;
				}
			} catch (InputMismatchException e) {
				System.out.println("정확하게 입력해주세요.");
				scan.nextLine();
				continue;
			}
		}
		scan.close();
	}
}