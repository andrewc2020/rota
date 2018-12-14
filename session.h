const enum group {CareManagers,ServiceManagers,Sysop};

class CSession : public CObject
		{
		public:
			virtual LRESULT GetSyncQueryName(CString&,CString);
		virtual	LRESULT GetDirection(DWORD&);
		 CSession();
		 ~CSession();
		 
		 		 
		 virtual enum group	GetGroup(void);
		 virtual LRESULT GetAppendQueryName(CString&,CString);

		};
	class CCareManagersSession : public CSession
		{
		public:
			virtual LRESULT GetSyncQueryName(CString&,CString);
		CCareManagersSession();
		 ~CCareManagersSession();
		 
		 virtual enum group	GetGroup(void);
		 virtual LRESULT GetAppendQueryName(CString&,CString);

		};
	class CServiceManagersSession : public CSession
		{
		public:
		 CServiceManagersSession();
		 ~CServiceManagersSession();
		 
		 virtual enum group	GetGroup(void);

		};

	class CSysopSession : public CSession
		{
		public:
			virtual LRESULT GetDirection(DWORD&);
		 CSysopSession();
		 ~CSysopSession();
		 
		 virtual enum group	GetGroup(void);

		};
