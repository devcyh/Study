package org.tukorea.atm.util;

import org.tukorea.atm.bank.Account;

public class Statistics {
	public static int sum(Account[] account, int size) {
		int sum = 0;
		for (int i = 0; i < size; i++)
			sum += account[i].getBalance();
		return sum;
	}

	public static double average(Account[] account, int size) {
		return (double) sum(account, size) / size;
	}

	public static int max(Account[] account, int size) {
		int max = account[0].getBalance();
		for (int i = 1; i < size; i++) {
			if (account[i].getBalance() > max)
				max = account[i].getBalance();
		}
		return max;
	}

	public static Account[] sort(Account[] account, int size) {
		Account key;
		for (int i = 1; i < size; i++) {
			key = account[i];
			int j = i;
			while (j > 0 && key.getBalance() > account[j - 1].getBalance()) {
				account[j] = account[j - 1];
				j--;
			}
			account[j] = key;
		}
		return account;
	}
}