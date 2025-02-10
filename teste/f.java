import java.io.*;

public class f 
{
	public static void main(String[] args)
	{	
		try
		{
			FileOutputStream fs = new FileOutputStream("teste.db");
			DataOutputStream dos = new DataOutputStream(fs);

			dos.writeUTF("Davi Ferreira Puddo");
			dos.writeInt(19);
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}	
		
	}
}
