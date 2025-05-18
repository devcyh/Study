package org.tukorea.ticketbox.util;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Set;

import org.tukorea.ticketbox.payment.Receipt;

public class Statistics {
	public static double sum(HashMap<Integer, Receipt> map) {
		Set<Integer> keys = map.keySet();
		Iterator<Integer> it = keys.iterator();
		double sum = 0;
		while (it.hasNext())
			sum += map.get(it.next()).getTotalAmount();
		return sum;
	}
}