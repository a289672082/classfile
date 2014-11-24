// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类

#import "E:\\乱研究\\MyDialog\\Release\\dm3.dll" no_namespace
// CEyLoginSoft 包装类

class CEyLoginSoft : public COleDispatchDriver
{
public:
	CEyLoginSoft(){} // 调用 COleDispatchDriver 默认构造函数
	CEyLoginSoft(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CEyLoginSoft(const CEyLoginSoft& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 特性
public:

	// 操作
public:


	// IEyLoginSoft 方法
public:
	CString Ver()
	{
		CString result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void SetAppKey(LPCTSTR appKey)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, appKey);
	}
	long GetLastError()
	{
		long result;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString GetLastMessages()
	{
		CString result;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString GetLatestVersion()
	{
		CString result;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString GetLatestVersionName()
	{
		CString result;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString GetCurrentVersionName()
	{
		CString result;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString GetAppCode()
	{
		CString result;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString GetVersionCode()
	{
		CString result;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString GetBulletin()
	{
		CString result;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString GetUserExpired()
	{
		CString result;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long UserLogin(LPCTSTR userName, LPCTSTR userPwd, LPCTSTR appVer, LPCTSTR userMac)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_I4, (void*)&result, parms, userName, userPwd, appVer, userMac);
		return result;
	}
	long UserRegin(LPCTSTR userName, LPCTSTR userPwd, LPCTSTR userEmail, LPCTSTR userMac)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_I4, (void*)&result, parms, userName, userPwd, userEmail, userMac);
		return result;
	}
	long UserRecharge(LPCTSTR userName, LPCTSTR cardPwd)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_I4, (void*)&result, parms, userName, cardPwd);
		return result;
	}
	long UpdatePwd(LPCTSTR userName, LPCTSTR userEmail)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_I4, (void*)&result, parms, userName, userEmail);
		return result;
	}
	CString GetExpired(LPCTSTR userName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, userName);
		return result;
	}
	long CheckUserStatus()
	{
		long result;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long CheckAppVersion(LPCTSTR aVer)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_I4, (void*)&result, parms, aVer);
		return result;
	}
	long UpdateUserExpiredDT(LPCTSTR userName, LPCTSTR userExpiredDT, LPCTSTR interfaceKey)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x13, DISPATCH_METHOD, VT_I4, (void*)&result, parms, userName, userExpiredDT, interfaceKey);
		return result;
	}
	long UserLoginSingle(LPCTSTR userCode, LPCTSTR aVer, LPCTSTR userMac)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_I4, (void*)&result, parms, userCode, aVer, userMac);
		return result;
	}
	long CheckUserStatusSingle()
	{
		long result;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long ConversionbindingMAC(LPCTSTR userCode, LPCTSTR newMAC)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_I4, (void*)&result, parms, userCode, newMAC);
		return result;
	}
	long ConversionbindingIP(LPCTSTR userCode)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_I4, (void*)&result, parms, userCode);
		return result;
	}
	long SingleRecharge(LPCTSTR userCode, LPCTSTR rechargeCard)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x18, DISPATCH_METHOD, VT_I4, (void*)&result, parms, userCode, rechargeCard);
		return result;
	}
	long UserConversionbindingMAC(LPCTSTR userName, LPCTSTR userPwd, LPCTSTR newMAC)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x19, DISPATCH_METHOD, VT_I4, (void*)&result, parms, userName, userPwd, newMAC);
		return result;
	}
	long LogOut()
	{
		long result;
		InvokeHelper(0x1a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long OpenUserCheck()
	{
		long result;
		InvokeHelper(0x1b, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long CloseUserCheck()
	{
		long result;
		InvokeHelper(0x1c, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString GetMACAddress()
	{
		CString result;
		InvokeHelper(0x1d, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString GetCpuID()
	{
		CString result;
		InvokeHelper(0x1e, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void SetUserCheckInterval(long interval)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, interval);
	}
	CString GetDiskSerial()
	{
		CString result;
		InvokeHelper(0x20, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString GetMachineCode()
	{
		CString result;
		InvokeHelper(0x21, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void SetMainFormHwnd(long hwnd)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x22, DISPATCH_METHOD, VT_EMPTY, NULL, parms, hwnd);
	}
	CString GetNetTime()
	{
		CString result;
		InvokeHelper(0x23, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long UserAddDays(LPCTSTR userName, long days, LPCTSTR interfaceKey)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_BSTR ;
		InvokeHelper(0x24, DISPATCH_METHOD, VT_I4, (void*)&result, parms, userName, days, interfaceKey);
		return result;
	}
	CString GetAppCodeRT()
	{
		CString result;
		InvokeHelper(0x25, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString GetBulletinRT()
	{
		CString result;
		InvokeHelper(0x26, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString GetOnlineStatus()
	{
		CString result;
		InvokeHelper(0x27, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long OpenUserCheckShowMessage(long times)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x28, DISPATCH_METHOD, VT_I4, (void*)&result, parms, times);
		return result;
	}
	CString GetVariable(__int64 id, LPCTSTR key)
	{
		CString result;
		static BYTE parms[] = VTS_I8 VTS_BSTR ;
		InvokeHelper(0x29, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, id, key);
		return result;
	}
	long RechargeEx(LPCTSTR uName, LPCTSTR cardPwd, LPCTSTR usert)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x2a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, uName, cardPwd, usert);
		return result;
	}
	long RechargeSingleEx(LPCTSTR uName, LPCTSTR cardPwd, LPCTSTR usert)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x2b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, uName, cardPwd, usert);
		return result;
	}
	CString GetUserData()
	{
		CString result;
		InvokeHelper(0x2c, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void SetUserData(LPCTSTR uData)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uData);
	}
	CString GenerateSpreadID()
	{
		CString result;
		InvokeHelper(0x2e, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void AutoUpdate(LPCTSTR Ver)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Ver);
	}
	void SetPath(LPCTSTR path)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x30, DISPATCH_METHOD, VT_EMPTY, NULL, parms, path);
	}
	long SingleExpireAddDays(LPCTSTR userCode, long days, LPCTSTR interfaceKey)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_BSTR ;
		InvokeHelper(0x31, DISPATCH_METHOD, VT_I4, (void*)&result, parms, userCode, days, interfaceKey);
		return result;
	}
	long GetOnlineCount(LPCTSTR userName, LPCTSTR userPwd)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x32, DISPATCH_METHOD, VT_I4, (void*)&result, parms, userName, userPwd);
		return result;
	}
	long CleanUserStates(LPCTSTR userName, LPCTSTR userPwd)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x33, DISPATCH_METHOD, VT_I4, (void*)&result, parms, userName, userPwd);
		return result;
	}
	void SetHost(LPCTSTR host)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x34, DISPATCH_METHOD, VT_EMPTY, NULL, parms, host);
	}

	// IEyLoginSoft 属性
public:

};
