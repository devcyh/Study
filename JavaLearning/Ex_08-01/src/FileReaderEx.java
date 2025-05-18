import java.io.*;

public class FileReaderEx {
	public static void main(String[] args) {
		FileInputStream fin = null;
		try {
			fin = new FileInputStream("C:\\temp\\FileReader\\1.txt");
			InputStreamReader in = new InputStreamReader(fin, "UTF-8");
			int c;
			while ((c = in.read()) != -1) {
				System.out.print((char) c);
			}
			fin.close();
		} catch (IOException e) {
			System.out.println("입출력 오류");
		}
	}
}