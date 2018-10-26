import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;

public class RabinKarp {
	public static void main(String[] args) throws IOException{
		String T,P;
		final int mod=13;
		
		BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
		T=input.readLine();
		P=input.readLine();
		
		int n=T.length();
		int m=P.length();
		
		// ������ ���̸� m�̶�� ���� �� �־��� ���ڿ��� ù��° ���� m��ŭ�� Horner's rule�� ����,
		// �� ������ Horner's rule�� ����
		int HASH_T = Horner(T,m);
		int HASH_P = Horner(P,m);
		
		
		// �־��� ���ڿ��� ���� Horner's rule�� �ٲ� ��� n-m+1���� ���´�.
		int HORNER_T[]=new int[n-m+1];
		HORNER_T[0]=HASH_T;
		
		// �־��� ���ڿ��� ù��°�� Horner's rule�� �̿��� ���ڷ� �ٲ� �� �װ� �̿��ؼ� ��� ������ ���Ѵ�..
		for(int i=1; i<=n-m; i++)
			HORNER_T[i]=10*(HORNER_T[i-1]-(int)Math.pow(10, m-1)*(T.charAt(i-1)-'0'))+(T.charAt(i+m-1)-'0');
		
		// ���ڷ� �ٲ� ���� ���ϱ⿡ �ʹ� Ŭ �� �ֱ� ������ mod�� �������� ���Ѵ�.
		// �� �� �迭�� ������ ������ ���� ������ HORNER_T�� ���� �Ͱ� ���� ������� ù��° �� �̿��ؼ� ���Ѵ�.
		int MOD_T[]=new int[n-m+1];
		int MOD_P = HASH_P%mod;
		MOD_T[0]=HASH_T%mod;
		int h = (int)Math.pow(10, m-1);
		for(int i=1; i<=n-m; i++)
			MOD_T[i]=(10*(HORNER_T[i-1]-(T.charAt(i-1)-'0')*h)+(T.charAt(i+m-1)-'0'))%mod;
		
		
		// ���Ͽ� �´� ���ڿ��� ã�´�.
		ArrayList<Integer> index=new ArrayList<Integer>();
		for(int i=0; i<=n-m; i++) {
			if(MOD_T[i]==MOD_P) {
				if(T.substring(i, i+m).equals(P)) {
					index.add(i+1);
				}
			}
		}
		
		System.out.println(index.size());
		for(int i=0; i<index.size(); i++) System.out.print(index.get(i)+" ");
		
		
	}
	
	static int Horner(String s, int m) {
		int res=0;
		for(int i=0; i<m; i++) {
			res+=(s.charAt(i)-'0')*(int)Math.pow(10, m-i-1);
		}
		return res;
	}
}
