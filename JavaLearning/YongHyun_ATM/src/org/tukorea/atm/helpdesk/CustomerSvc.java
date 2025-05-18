package org.tukorea.atm.helpdesk;

import org.tukorea.atm.bank.Account;

public class CustomerSvc {
	private Account[] accountArray; // 고객계좌배열 참조변수
	private int currentAccountNum; // 개설된 고객계좌 수

	public CustomerSvc(Account[] acctArray, int currentAcctNum) {
		accountArray = acctArray;
		currentAccountNum = currentAcctNum;
	}

	public void updatePasswdReq(int accountId, String oldPasswd, String newPasswd) {
		int index;
		for (index = 0; index < currentAccountNum; index++)// 입력한 id와 일치하는 배열 원소의 인덱스를 저장
			if (accountId == accountArray[index].getAccountId())
				break;
		if (index >= currentAccountNum) {
			System.out.println("존재하지 않는 계좌입니다.");
			return;
		}
		if (accountArray[index].updatePasswd(oldPasswd, newPasswd))
			System.out.println("비밀번호를 수정하였습니다.");
		else
			System.out.println("잘못된 비밀번호입니다.");
	}
}