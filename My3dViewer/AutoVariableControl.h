

#ifndef _AUTO_BOOL
#define _AUTO_BOOL


class CAutoBool
{
	public:
	BOOL* m_pBool;
	CAutoBool(BOOL* pBOOL)
	{
		m_pBool=NULL;
		m_pBool=pBOOL;

		if(m_pBool!=NULL)
		{
			*m_pBool=TRUE;
		}
	}

	~CAutoBool()
	{
		if(m_pBool)
			*m_pBool=FALSE;
	}
};

class CAutoLock
{
	public:
		CCriticalSection* m_Lock;
	CAutoLock(CCriticalSection* pLock)
	{
		m_Lock=pLock;
		m_Lock->Lock();
	}

	~CAutoLock()
	{
		m_Lock->Unlock();
	}
};

#endif