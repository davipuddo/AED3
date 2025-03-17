package entity;

public interface FileEntity 
{
	public void setID (int x);
	public int getID ();
	public byte[] toByteArray() throws Exception;
	public void fromByteArray(byte[] data) throws Exception;
}
