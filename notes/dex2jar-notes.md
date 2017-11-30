# Some interesting notes while reverse engeneering the .dex files from the vstar android application

```java
    // SL = AF820 Smart Light
    // Comments are mine
    // These correspond to ports used by the SL
    public static final int LocalFindPort = 5879; // Not sure what Find is for
    public static final int LocalUdpPort = 5880;  // but this port is always used by the SL to receive and send udp packets

    // found this somewhere to
    this.regServiceIp = InetAddress.getByName("198.199.115.33");

    // This is the port that the remote registration service uses
    public static final int RemoteRegServicePort = 30001;

    // These align with some of the functions the SL uses
    // Since these are unsigned bytes we read them like:                         this
    public static final byte FunCheck = -1;                                     // 0xFF  status check
    public static final byte FunCheckBack = -2;                                 // 0xFE  status check response
    public static final byte FunLightOpen = 1;                                  // 0x01  on
    public static final byte FunLightClose = 2;                                 // 0x02  off
    public static final byte FunLightColor = 3;                                 // 0x03  color
    public static final byte FunLightRandom = 4;                                // 0x04  random
    public static final byte FunLightSleep = 5;                                 // 0x05  sleep
    public static final byte FunReg = -5;                                       // 0xFB  register request
    public static final byte FunRegBack = -6;                                   // 0xFA  register response
    public static final byte FunReset = -9;                                     // 0xF7  reset
    public static final byte FunWiFiConfig = -16;                               // 0xF0  wifi


    // stuf we are unsure about
    public static final byte FunGetGateWayMac = 4;                               // 0x04 -> probably not SL
    public static final int ConnectLocal = 1;
    public static final int ConnectNull = 0;
    public static final int ConnectNullIcon = 3;
    public static final int ConnectRemote = 2;
    public static final byte[] FunControllersSwitch;
    public static final byte[] FunControllersTimeOff = { 18, 34, 50, 66 };
    public static final byte[] FunControllersTimeOn;

    // maybe the type of Smart Device
    public static final byte TypeBigLight = 33;
    public static final byte TypeController = 17;
    public static final byte TypeCurtain = 80;
    public static final byte TypeFreeStickers = 49;
    public static final byte TypeGateWay = 1;
    public static final byte TypeInfra = 48;
    public static final byte TypeInfraAir = 49;
    public static final byte TypeInfraCamera = 51;
    public static final byte TypeInfraTv = 50;
    public static final byte TypeLight = 32;
    public static final byte TypeNull = 0;
    public static final byte TypePlug = 16;
    public static final byte TypePublic = 0;
    public static final byte TypeTakePic = 67;

    // code about checking validity of packet
    public class PacketCheck
    {
        public static final int BASICLEN = 37;          // 0x25 - default length of packet
        // seems like there is a difference in header for local and phone packages?
        public static final byte HEADH = 85;            // 0x55 - packet always starts with this
        public static final byte HEADL = -86;           // 0xAA - packet always starts with this or 0x66
        // phone vs local?
        public static final byte PHONEHEADH = 85;       // 0x55 - packet always starts with this
        public static final byte PHONEHEADL = 102;      // 0x66 - packet always starts with this or 0xAA

        // the first 37 bytes of the packet (?)
        public byte[] data;

        // 32 bit int -> 4 bytes
        public int controlDevId;
        public byte devcode;
        public byte devfun;
        public byte devver;
        // IPv4 address -> 4 bytes
        public InetAddress ip;
        // total length of the packet
        int len;
        // 64 bit int -> 8 bytes
        public long mac;

        // so port is 32 bit integer -> seems weird but ok
        public int port;
        // sequence number is weird to be 32 bit. Because in the packet it has only 16 bits available and can never be 0
        public int seq;
        // the extra data bytes of the packet
        public byte[] xdata;
        // extra data length of packet
        public int xdatalen;

        public PacketCheck(byte[] paramArrayOfByte, int paramInt1, InetAddress paramInetAddress, int paramInt2)
        {
            this.data = paramArrayOfByte;
            this.len = paramInt1;
            this.ip = paramInetAddress;
            this.port = paramInt2;
            this.mac = 0L;
            this.controlDevId = 0;
        }

        public boolean check()
        {
            if (this.data == null) {
                return false;
            }
            if (this.len < 37) {
                return false;
            }
            if ((this.data[0] != 85) && (this.data[0] != 85)) {
                return false;
            }
            if ((this.data[1] != -86) && (this.data[1] != 102)) {
                return false;
            }
            if (DataExchange.twoByteToInt(this.data[2], this.data[3]) != this.len) {
                return false;
            }
            this.mac = DataExchange.eightByteToLong(this.data[7], this.data[8], this.data[9], this.data[10], this.data[11], this.data[12], this.data[13], this.data[14]);
            this.controlDevId = DataExchange.fourByteToInt(this.data[23], this.data[24], this.data[25], this.data[26]);
            this.devfun = this.data[20];
            this.devver = this.data[19];
            this.devcode = this.data[18];
            this.seq = DataExchange.twoByteToInt(this.data[31], this.data[32]);
            this.xdatalen = DataExchange.twoByteToInt(this.data[33], this.data[34]);
            this.xdata = new byte[this.xdatalen];
            System.arraycopy(this.data, 37, this.xdata, 0, this.xdatalen);
            return true;
        }
    }

    // code about light control packet
    package elle.home.protocol;

    import elle.home.publicfun.DataExchange;
    import elle.home.publicfun.PublicDefine;
    import java.net.InetAddress;

    public class LightControlPacket
    extends BasicPacket
    {
        public LightControlPacket(InetAddress paramInetAddress, int paramInt)
        {
            super(paramInetAddress, paramInt);
        }

        public void lightCheck(byte[] paramArrayOfByte, OnRecvListener paramOnRecvListener)
        {
            super.packData((byte)32, (byte)0, (byte)-1, paramArrayOfByte, PublicDefine.phonemac, PublicDefine.getSeq(), null);
            super.setListener(paramOnRecvListener);
        }

        public void lightClose(byte[] paramArrayOfByte, OnRecvListener paramOnRecvListener)
        {
            super.packData((byte)32, (byte)0, (byte)2, paramArrayOfByte, PublicDefine.getPhoneMac(), PublicDefine.getSeq(), null);
            super.setListener(paramOnRecvListener);
        }

        public void lightColor(byte[] paramArrayOfByte, OnRecvListener paramOnRecvListener, int paramInt1, int paramInt2, int paramInt3, int paramInt4, int paramInt5, int paramInt6)
        {
            byte[] arrayOfByte = new byte[12];
            System.arraycopy(DataExchange.intToTwoByte(paramInt1), 0, arrayOfByte, 0, 2);
            System.arraycopy(DataExchange.intToTwoByte(paramInt2), 0, arrayOfByte, 2, 2);
            System.arraycopy(DataExchange.intToTwoByte(paramInt3), 0, arrayOfByte, 4, 2);
            System.arraycopy(DataExchange.intToTwoByte(paramInt4), 0, arrayOfByte, 6, 2);
            System.arraycopy(DataExchange.intToTwoByte(paramInt6), 0, arrayOfByte, 8, 2);
            System.arraycopy(DataExchange.intToTwoByte(paramInt5), 0, arrayOfByte, 10, 2);
            super.packData((byte)32, (byte)0, (byte)3, paramArrayOfByte, PublicDefine.getPhoneMac(), PublicDefine.getSeq(), arrayOfByte);
            super.setListener(paramOnRecvListener);
        }

        public void lightFree(byte[] paramArrayOfByte, OnRecvListener paramOnRecvListener, boolean paramBoolean)
        {
            byte[] arrayOfByte = new byte[1];
            if (paramBoolean) {
                arrayOfByte[0] = 1;
            }
            for (;;)
            {
                super.packData((byte)32, (byte)0, (byte)4, paramArrayOfByte, PublicDefine.getPhoneMac(), PublicDefine.getSeq(), arrayOfByte);
                super.setListener(paramOnRecvListener);
                return;
                arrayOfByte[0] = 0;
            }
        }

        public void lightOpen(byte[] paramArrayOfByte, OnRecvListener paramOnRecvListener)
        {
            super.packData((byte)32, (byte)0, (byte)1, paramArrayOfByte, PublicDefine.getPhoneMac(), PublicDefine.getSeq(), null);
            super.setListener(paramOnRecvListener);
        }

        public void lightSleep(byte[] paramArrayOfByte, OnRecvListener paramOnRecvListener, int paramInt)
        {
            byte[] arrayOfByte = new byte[2];
            System.arraycopy(DataExchange.intToTwoByte(paramInt), 0, arrayOfByte, 0, 2);
            super.packData((byte)32, (byte)0, (byte)5, paramArrayOfByte, PublicDefine.getPhoneMac(), PublicDefine.getSeq(), arrayOfByte);
            super.setListener(paramOnRecvListener);
        }
    }


    // code about packing the packets in zigbee (bluetooth?) format
    package elle.home.protocol.zigbee;

    import elle.home.database.OneDev;
    import elle.home.publicfun.DataExchange;
    import elle.home.publicfun.PublicDefine;

    public class ZigBasicPacket
    {
        public static final int BasicLen = 37;
        public static final int ImportHigh = 2;
        public static final int ImportLow = 0;
        public static final int ImportNormal = 1;
        public static final int ImportStatic = 3;
        public byte[] data;
        public int importance = 1;
        public boolean isRemote = false;
        public int recvcount = 0;
        public int sendcount = 0;
        public int sendtime = 0;
        public int seq;

        public int couldSend(int paramInt)
        {
            if (Math.abs(paramInt - this.sendtime) < 3) {
                return 0;
            }
            this.sendtime = paramInt;
            this.sendcount += 1;
            return this.sendcount;
        }

        public byte[] getData()
        {
            return this.data;0
        }

        public int getImportance()
        {
            return this.importance;
        }

        public int getSeq()
        {
            return this.seq;
        }

        public void packCheckPacket(int paramInt)
        {
            packData((byte)0, (byte)0, (byte)-1, new byte[8], PublicDefine.phonemac, paramInt, null);
        }

        public void packCheckPacket(OneDev paramOneDev, int paramInt)
        {
            packData(paramOneDev.type, paramOneDev.ver, (byte)-1, DataExchange.longToEightByte(paramOneDev.mac), PublicDefine.getPhoneMac(), PublicDefine.getSeq(), null);
        }

        public void packCheckPacket(byte[] paramArrayOfByte, int paramInt)
        {
            packData((byte)0, (byte)0, (byte)-1, paramArrayOfByte, PublicDefine.phonemac, paramInt, null);
        }

        public void packData(byte paramByte1, byte paramByte2, byte paramByte3, byte[] paramArrayOfByte1, byte[] paramArrayOfByte2, int paramInt, byte[] paramArrayOfByte3)
        {
            packData(paramByte1, paramByte2, paramByte3, paramArrayOfByte1, paramArrayOfByte2, paramInt, paramArrayOfByte3, (byte)0, (byte)0);
        }

        public void packData(byte paramByte1, byte paramByte2, byte paramByte3, byte[] paramArrayOfByte1, byte[] paramArrayOfByte2, int paramInt, byte[] paramArrayOfByte3, byte paramByte4, byte paramByte5)
        {
            this.seq = paramInt;
            if (paramArrayOfByte3 != null) {}
            for (this.data = new byte[paramArrayOfByte3.length + 37];; this.data = new byte[37])
            {
                byte[] arrayOfByte1 = this.data;
                int j = 0 + 1;
                arrayOfByte1[0] = 102;
                arrayOfByte1 = this.data;
                int i = j + 1;
                arrayOfByte1[j] = -86;
                arrayOfByte1 = DataExchange.intToTwoByte(paramArrayOfByte3.length + 37);
                byte[] arrayOfByte2 = this.data;
                j = i + 1;
                arrayOfByte2[i] = arrayOfByte1[0];
                arrayOfByte2 = this.data;
                i = j + 1;
                arrayOfByte2[j] = arrayOfByte1[1];
                arrayOfByte1 = this.data;
                j = i + 1;
                arrayOfByte1[i] = 1;
                arrayOfByte1 = this.data;
                i = j + 1;
                arrayOfByte1[j] = 0;
                arrayOfByte1 = this.data;
                j = i + 1;
                arrayOfByte1[i] = 0;
                System.arraycopy(paramArrayOfByte1, 0, this.data, j, 8);
                j += 8;
                paramArrayOfByte1 = this.data;
                i = j + 1;
                paramArrayOfByte1[j] = 0;
                paramArrayOfByte1 = this.data;
                j = i + 1;
                paramArrayOfByte1[i] = 0;
                paramArrayOfByte1 = this.data;
                i = j + 1;
                paramArrayOfByte1[j] = 0;
                paramArrayOfByte1 = this.data;
                j = i + 1;
                paramArrayOfByte1[i] = paramByte1;
                paramArrayOfByte1 = this.data;
                i = j + 1;
                paramArrayOfByte1[j] = paramByte2;
                paramArrayOfByte1 = this.data;
                j = i + 1;
                paramArrayOfByte1[i] = paramByte3;
                paramArrayOfByte1 = this.data;
                i = j + 1;
                paramArrayOfByte1[j] = paramByte4;
                paramArrayOfByte1 = this.data;
                j = i + 1;
                paramArrayOfByte1[i] = paramByte5;
                System.arraycopy(paramArrayOfByte2, 0, this.data, j, 4);
                i = j + 4 + 4;
                paramArrayOfByte1 = DataExchange.intToTwoByte(paramInt);
                paramArrayOfByte2 = this.data;
                paramInt = i + 1;
                paramArrayOfByte2[i] = paramArrayOfByte1[0];
                paramArrayOfByte2 = this.data;
                i = paramInt + 1;
                paramArrayOfByte2[paramInt] = paramArrayOfByte1[1];
                paramArrayOfByte1 = DataExchange.intToTwoByte(paramArrayOfByte3.length);
                paramArrayOfByte2 = this.data;
                paramInt = i + 1;
                paramArrayOfByte2[i] = paramArrayOfByte1[0];
                paramArrayOfByte2 = this.data;
                i = paramInt + 1;
                paramArrayOfByte2[paramInt] = paramArrayOfByte1[1];
                paramArrayOfByte1 = this.data;
                paramInt = i + 1;
                paramArrayOfByte1[i] = 0;
                this.data[paramInt] = 0;
                System.arraycopy(paramArrayOfByte3, 0, this.data, paramInt + 1, paramArrayOfByte3.length);
                paramInt = paramArrayOfByte3.length;
                return;
                paramArrayOfByte3 = new byte[0];
            }
        }

        public void packRegPacket(OneDev paramOneDev, int paramInt)
        {
            packData(paramOneDev.type, paramOneDev.ver, (byte)-5, DataExchange.longToEightByte(paramOneDev.mac), PublicDefine.getPhoneMac(), PublicDefine.getSeq(), null);
        }

        public void packReset(OneDev paramOneDev)
        {
            packData(paramOneDev.type, paramOneDev.ver, (byte)-9, DataExchange.longToEightByte(paramOneDev.mac), PublicDefine.getPhoneMac(), PublicDefine.getSeq(), null);
        }

        public void packWiFiConfigCheck(OneDev paramOneDev)
        {
            packData(paramOneDev.type, paramOneDev.ver, (byte)-16, DataExchange.longToEightByte(paramOneDev.mac), PublicDefine.getPhoneMac(), PublicDefine.getSeq(), new byte[] { 1 });
        }

        public void packWifiConfigRestart(OneDev paramOneDev)
        {
            packData(paramOneDev.type, paramOneDev.ver, (byte)-16, DataExchange.longToEightByte(paramOneDev.mac), PublicDefine.getPhoneMac(), PublicDefine.getSeq(), new byte[] { 5 });
        }

        public void packWifiConfigSet(OneDev paramOneDev, String paramString1, String paramString2)
        {
            byte[] arrayOfByte = new byte[paramString1.length() + paramString2.length() + 3];
            arrayOfByte[0] = 3;
            arrayOfByte[1] = ((byte)(paramString1.length() & 0xFF));
            System.arraycopy(paramString1.getBytes(), 0, arrayOfByte, 2, paramString1.length());
            arrayOfByte[(paramString1.length() + 2)] = ((byte)(paramString2.length() & 0xFF));
            System.arraycopy(paramString2.getBytes(), 0, arrayOfByte, paramString1.length() + 3, paramString2.length());
            packData(paramOneDev.type, paramOneDev.ver, (byte)-16, DataExchange.longToEightByte(paramOneDev.mac), PublicDefine.getPhoneMac(), PublicDefine.getSeq(), arrayOfByte);
        }

        public void packZigbeeData(byte paramByte1, byte paramByte2, byte paramByte3, byte[] paramArrayOfByte1, byte[] paramArrayOfByte2, int paramInt, byte[] paramArrayOfByte3)
        {
            packData(paramByte1, paramByte2, paramByte3, paramArrayOfByte1, paramArrayOfByte2, paramInt, paramArrayOfByte3, (byte)1, (byte)1);
        }

        public void packZigbeeReset(OneDev paramOneDev)
        {
            packZigbeeData(paramOneDev.type, paramOneDev.ver, (byte)-9, DataExchange.longToEightByte(paramOneDev.mac), PublicDefine.getPhoneMac(), PublicDefine.getSeq(), null);
        }

        public void setImportance(int paramInt)
        {
            this.importance = paramInt;
        }

        public void setPacketRemote(boolean paramBoolean)
        {
            this.isRemote = paramBoolean;
        }
    }

```
```java
// stuff about handling the raw UDP data packets
package elle.home.protocol;

import java.net.DatagramPacket;
import java.util.ArrayList;
import java.util.Timer;
import java.util.TimerTask;

public class ProtocolDataList
{
  public String TAG = "ProtocolDataList";
  LocalDevCheckList checktmplist;
  public ArrayList<BasicPacket> sendList = new ArrayList();
  public int sendtime;
  TimerTask task = new ProtocolDataList.1(this);
  Timer timer = new Timer();

  public ProtocolDataList()
  {
    this.timer.schedule(this.task, 200L, 100L);
  }

  public void StopTimer()
  {
    this.timer.cancel();
  }

  public void addOnePacketToSend(BasicPacket paramBasicPacket)
  {
    try
    {
      if (this.sendList != null) {
        this.sendList.add(paramBasicPacket);
      }
      return;
    }
    finally
    {
      paramBasicPacket = finally;
      throw paramBasicPacket;
    }
  }

  public void dealRecvPacket(PacketCheck paramPacketCheck)
  {
    for (;;)
    {
      int i;
      try
      {
        i = paramPacketCheck.seq;
        if (i == 0) {
          return;
        }
        if ((this.sendList == null) || (this.sendList.size() <= 0)) {
          continue;
        }
        i = 0;
        if (i >= this.sendList.size()) {
          continue;
        }
        if (((BasicPacket)this.sendList.get(i)).getSeq() != paramPacketCheck.seq) {
          break label261;
        }
        if (((BasicPacket)this.sendList.get(i)).getImportance() != 3) {
          break label214;
        }
        BasicPacket localBasicPacket = (BasicPacket)this.sendList.get(i);
        localBasicPacket.recvcount += 1;
        if (((BasicPacket)this.sendList.get(i)).recvcount == 1)
        {
          ((BasicPacket)this.sendList.get(i)).sendcount = 5;
          continue;
        }
        if (((BasicPacket)this.sendList.get(i)).recvcount < 2) {
          break label202;
        }
      }
      finally {}
      if (((BasicPacket)this.sendList.get(i)).listener != null)
      {
        ((BasicPacket)this.sendList.get(i)).listener.OnRecvData(paramPacketCheck);
        continue;
        label202:
        this.sendList.remove(i);
        continue;
        label214:
        if (((BasicPacket)this.sendList.get(i)).listener != null) {
          ((BasicPacket)this.sendList.get(i)).listener.OnRecvData(paramPacketCheck);
        }
        this.sendList.remove(i);
        continue;
        label261:
        i += 1;
      }
    }
  }

  public void delOnePacketFromList(int paramInt)
  {
    try
    {
      if ((this.sendList != null) && (this.sendList.size() > 0))
      {
        int i = 0;
        while (i < this.sendList.size())
        {
          if (((BasicPacket)this.sendList.get(i)).seq == paramInt) {
            this.sendList.remove(i);
          }
          i += 1;
        }
      }
      return;
    }
    finally {}
  }

  public DatagramPacket getOnePacketFromSendList()
  {
    for (;;)
    {
      int i;
      try
      {
        if ((this.sendList == null) || (this.sendList.size() <= 0)) {
          break label444;
        }
        i = 0;
        if (i >= this.sendList.size()) {
          break label444;
        }
        DatagramPacket localDatagramPacket1;
        if (((BasicPacket)this.sendList.get(i)).getImportance() == 0)
        {
          localDatagramPacket1 = ((BasicPacket)this.sendList.get(i)).getUdpData();
          this.sendList.remove(i);
          return localDatagramPacket1;
        }
        if (((BasicPacket)this.sendList.get(i)).getImportance() == 1)
        {
          j = ((BasicPacket)this.sendList.get(i)).couldSend(this.sendtime);
          if ((j >= 1) && (j <= 3))
          {
            localDatagramPacket1 = ((BasicPacket)this.sendList.get(i)).getUdpData();
            continue;
          }
          if (j <= 5) {
            break label437;
          }
          if (((BasicPacket)this.sendList.get(i)).listener != null) {
            ((BasicPacket)this.sendList.get(i)).listener.OnRecvData(null);
          }
          this.sendList.remove(i);
          break label444;
        }
        if (((BasicPacket)this.sendList.get(i)).getImportance() == 3)
        {
          j = ((BasicPacket)this.sendList.get(i)).couldSend(this.sendtime);
          if ((j > 0) && (j <= 3))
          {
            localDatagramPacket1 = ((BasicPacket)this.sendList.get(i)).getUdpData();
            continue;
          }
          if (j != 25) {
            break label437;
          }
          if (((BasicPacket)this.sendList.get(i)).listener != null) {
            ((BasicPacket)this.sendList.get(i)).listener.OnRecvData(null);
          }
          if (i >= this.sendList.size()) {
            break label444;
          }
          this.sendList.remove(i);
        }
      }
      finally {}
      int j = ((BasicPacket)this.sendList.get(i)).couldSend(this.sendtime);
      DatagramPacket localDatagramPacket2;
      if ((j > 0) && (j <= 5))
      {
        localDatagramPacket2 = ((BasicPacket)this.sendList.get(i)).getUdpData();
      }
      else
      {
        if (j > 7)
        {
          if (((BasicPacket)this.sendList.get(i)).listener != null) {
            ((BasicPacket)this.sendList.get(i)).listener.OnRecvData(null);
          }
          if (i < this.sendList.size()) {
            this.sendList.remove(i);
          }
        }
        else
        {
          label437:
          i += 1;
          continue;
        }
        label444:
        localDatagramPacket2 = null;
      }
    }
  }

  public void setCheckListTmp(LocalDevCheckList paramLocalDevCheckList)
  {
    this.checktmplist = paramLocalDevCheckList;
  }
}
```

```java
// something about a shake service
// only interesting because of the ip '255.255.255.255' which is the broadcast adress
package elle.home.shake;

import android.app.Service;
import android.content.Intent;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.media.AudioManager;
import android.media.SoundPool;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Handler;
import android.os.IBinder;
import android.os.PowerManager.WakeLock;
import elle.home.database.AllDevInfo;
import elle.home.database.OneDev;
import elle.home.protocol.LightControlPacket;
import elle.home.protocol.LuminaireControlPacket;
import elle.home.publicfun.DataExchange;
import elle.home.utils.SaveDataPreferences;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.Calendar;
import java.util.Iterator;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;
import vstc.vscam.utilss.LogTools;

public class ShakeService
  extends Service
{
  private static final int DAYTIME_BEGIN = 7;
  private static final int DAYTIME_END = 19;
  private static final int RESPONSE_COUNTER = 3;
  private static final int RESPONSE_DELAY = 800;
  private static final String TAG = "ShakeService";
  private static final int VIB_TIMER = 600;
  public DatagramSocket dataSocket;
  Handler handler = new Handler();
  private AllDevInfo mAllDevInfo;
  private long mLastShakeTime = 0L;
  private int mShakeCounter = 0;
  Runnable response = new Runnable()
  {
    public void run()
    {
      ShakeService.this.onExecControl();
    }
  };
  private SensorEventListener sensorEventListener = new SensorEventListener()
  {
    public void onAccuracyChanged(Sensor paramAnonymousSensor, int paramAnonymousInt) {}

    public void onSensorChanged(SensorEvent paramAnonymousSensorEvent)
    {
      paramAnonymousSensorEvent = paramAnonymousSensorEvent.values;
      float f1 = paramAnonymousSensorEvent[0];
      float f2 = paramAnonymousSensorEvent[1];
      float f3 = paramAnonymousSensorEvent[2];
      if ((Math.abs(f1) > 19) || (Math.abs(f2) > 19) || (Math.abs(f3) > 19)) {
        ShakeService.this.onShake();
      }
    }
  };
  private int soundId_off;
  private int soundId_on;
  private SoundPool soundPool;
  private PowerManager.WakeLock wakeLock = null;

  private boolean checkFunction(String paramString1, String paramString2)
  {
    return (paramString2 != null) && (paramString2.contains(paramString1));
  }

  private DatagramPacket getLightPacket(boolean paramBoolean, OneDev paramOneDev)
  {
    LightControlPacket localLightControlPacket = new LightControlPacket(null, 5880);
    localLightControlPacket.setImportance(2);
    try
    {
      localLightControlPacket.setIp(InetAddress.getByName("255.255.255.255"));
      if (paramBoolean)
      {
        localLightControlPacket.lightClose(DataExchange.longToEightByte(paramOneDev.mac), null);
        return localLightControlPacket.getUdpData();
      }
    }
    catch (UnknownHostException localUnknownHostException)
    {
      for (;;)
      {
        localUnknownHostException.printStackTrace();
        continue;
        localLightControlPacket.lightOpen(DataExchange.longToEightByte(paramOneDev.mac), null);
      }
    }
  }

  private DatagramPacket getLuminairePacket(boolean paramBoolean, OneDev paramOneDev)
  {
    LuminaireControlPacket localLuminaireControlPacket = new LuminaireControlPacket(null, 5880);
    localLuminaireControlPacket.setImportance(2);
    try
    {
      localLuminaireControlPacket.setIp(InetAddress.getByName("255.255.255.255"));
      LogTools.e("vstturn off getLuminairePacket");
      if (paramBoolean)
      {
        localLuminaireControlPacket.lightClose(DataExchange.longToEightByte(paramOneDev.mac), null);
        return localLuminaireControlPacket.getUdpData();
      }
    }
    catch (UnknownHostException localUnknownHostException)
    {
      for (;;)
      {
        localUnknownHostException.printStackTrace();
        continue;
        localLuminaireControlPacket.lightOpen(DataExchange.longToEightByte(paramOneDev.mac), null);
      }
    }
  }

  private boolean isNetworkEnabled()
  {
    NetworkInfo localNetworkInfo = ((ConnectivityManager)getSystemService("connectivity")).getActiveNetworkInfo();
    return (localNetworkInfo != null) && (localNetworkInfo.isConnected()) && (localNetworkInfo.getType() == 1);
  }

  private void playSound(boolean paramBoolean)
  {
    AudioManager localAudioManager = (AudioManager)getSystemService("audio");
    float f = localAudioManager.getStreamVolume(3) / localAudioManager.getStreamMaxVolume(3);
    if (paramBoolean)
    {
      this.soundPool.play(this.soundId_off, f, f, 1, 0, 1.0F);
      return;
    }
    this.soundPool.play(this.soundId_on, f, f, 1, 0, 1.0F);
  }

  private void sendPacket()
  {
    boolean bool1 = true;
    boolean bool2 = SaveDataPreferences.loadBoolean(this, "LIGHT_ON", true);
    int i = 0;
    Iterator localIterator = this.mAllDevInfo.alldevinfo.iterator();
    while (localIterator.hasNext())
    {
      final Object localObject = (OneDev)localIterator.next();
      if (checkFunction("shake_on", ((OneDev)localObject).function))
      {
        LogTools.e("vstturn off " + bool2);
        i = 1;
        if (32 == ((OneDev)localObject).type) {}
        for (localObject = getLightPacket(bool2, (OneDev)localObject);; localObject = getLuminairePacket(bool2, (OneDev)localObject))
        {
          new Thread()
          {
            public void run()
            {
              try
              {
                ShakeService.this.dataSocket.send(localObject);
                ShakeService.this.dataSocket.send(localObject);
                ShakeService.this.dataSocket.send(localObject);
                return;
              }
              catch (IOException localIOException)
              {
                localIOException.printStackTrace();
              }
            }
          }.start();
          break;
        }
      }
    }
    if (i != 0) {
      playSound(bool2);
    }
    if (!bool2) {}
    for (;;)
    {
      SaveDataPreferences.saveBoolean(this, "LIGHT_ON", bool1);
      return;
      bool1 = false;
    }
  }

  public boolean isDayTime()
  {
    int i = Calendar.getInstance().get(11);
    return (i >= 7) && (i < 19);
  }

  public IBinder onBind(Intent paramIntent)
  {
    return null;
  }

  public void onCreate()
  {
    super.onCreate();
    this.soundPool = new SoundPool(3, 3, 0);
    this.soundPool = new SoundPool(4, 3, 100);
    this.mAllDevInfo = new AllDevInfo(this);
    try
    {
      this.dataSocket = new DatagramSocket();
      return;
    }
    catch (SocketException localSocketException)
    {
      localSocketException.printStackTrace();
    }
  }

  public void onDestroy()
  {
    super.onDestroy();
    LogTools.e(" shareserive onDestroy() 1");
    if (this.dataSocket != null)
    {
      this.dataSocket.disconnect();
      new Timer().schedule(new TimerTask()
      {
        public void run()
        {
          ShakeService.this.dataSocket.close();
        }
      }, 500L);
    }
    LogTools.e("shakeservice");
    LogTools.e("shareserive onDestroy() 2");
  }

  public void onExecControl()
  {
    this.mShakeCounter = 0;
    if (isNetworkEnabled())
    {
      this.mAllDevInfo.getAllDev();
      if (!isDayTime()) {
        break label43;
      }
      if (SaveDataPreferences.loadBoolean(this, "SHAKE_DAY", true)) {
        sendPacket();
      }
    }
    label43:
    while (!SaveDataPreferences.loadBoolean(this, "SHAKE_NIGHT", true)) {
      return;
    }
    sendPacket();
  }

  public void onShake()
  {
    if (Math.abs(this.mLastShakeTime - System.currentTimeMillis()) > 800L) {
      this.mShakeCounter = 0;
    }
    this.mShakeCounter += 1;
    if (this.mShakeCounter >= 3)
    {
      this.handler.removeCallbacks(this.response);
      this.handler.postDelayed(this.response, 800L);
    }
    this.mLastShakeTime = System.currentTimeMillis();
  }

  public int onStartCommand(Intent paramIntent, int paramInt1, int paramInt2)
  {
    return super.onStartCommand(paramIntent, paramInt1, paramInt2);
  }

  public boolean onUnbind(Intent paramIntent)
  {
    LogTools.e(" shareserive onUnbind() 1");
    return super.onUnbind(paramIntent);
  }
}

```
