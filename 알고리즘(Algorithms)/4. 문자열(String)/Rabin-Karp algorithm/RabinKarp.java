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
		
		// 패턴의 길이를 m이라고 했을 때 주어진 문자열의 첫번째 길이 m만큼을 Horner's rule로 변경,
		// 또 패턴을 Horner's rule로 변경
		int HASH_T = Horner(T,m);
		int HASH_P = Horner(P,m);
		
		
		// 주어진 문자열을 전부 Horner's rule로 바꿀 경우 n-m+1개가 나온다.
		int HORNER_T[]=new int[n-m+1];
		HORNER_T[0]=HASH_T;
		
		// 주어진 문자열의 첫번째만 Horner's rule을 이용해 숫자로 바꾼 뒤 그걸 이용해서 계속 다음걸 구한다..
		for(int i=1; i<=n-m; i++)
			HORNER_T[i]=10*(HORNER_T[i-1]-(int)Math.pow(10, m-1)*(T.charAt(i-1)-'0'))+(T.charAt(i+m-1)-'0');
		
		// 숫자로 바꾼 값이 비교하기에 너무 클 수 있기 때문에 mod로 나머지를 구한다.
		// 이 때 배열의 각각을 나누지 말고 위에서 HORNER_T를 구한 것과 같은 방법으로 첫번째 걸 이용해서 구한다.
		int MOD_T[]=new int[n-m+1];
		int MOD_P = HASH_P%mod;
		MOD_T[0]=HASH_T%mod;
		int h = (int)Math.pow(10, m-1);
		for(int i=1; i<=n-m; i++)
			MOD_T[i]=(10*(HORNER_T[i-1]-(T.charAt(i-1)-'0')*h)+(T.charAt(i+m-1)-'0'))%mod;
		
		
		// 패턴에 맞는 문자열을 찾는다.
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
