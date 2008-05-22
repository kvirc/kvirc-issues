//mdm:
//   File : class_tbrowser.cpp
//   Creation date : Fri Jan 28 14:21:48 CEST 2005
//   by Tonino Imbesi(Grifisx) and Alessandro Carbone(Noldor)
//
//   This file is part of the KVirc irc client distribution
//   Copyright (C) 1999-2005 Szymon Stefanek (pragma at kvirc dot net)
//
//   This program is FREE software. You can redistribute it and/or
//   modify it under the terms of the GNU General Public License
//   as published by the Free Software Foundation; either version 2
//   of the License, or (at your opinion) any later version.
//
//   This program is distributed in the HOPE that it will be USEFUL,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//   See the GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program. If not, write to the Free Software Foundation,
//   Inc. ,59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//


#include "class_tbrowser.h"
#include "kvi_error.h"
#include "kvi_debug.h"
#include "kvi_locale.h"
#include "kvi_iconmanager.h"

#include <QTextBrowser>
#include <QFile>
/*
	@doc: textbrowser
	@keyterms:
		textbrowser browser widget class,
	@title:
		textbrowser class
	@type:
		class
	@short:
		Provides a class that can display html pages.
	@inherits:
		[class]widget[/class]
	@description:
		Provides a class that can display html pages with hypertext navigation.
	@functions:
		!fn: $setSource(<file_name:string>)
		With this you can display the page at szFile location (szFile include the path).
		!fn: $backward()
		Changes the document displayed to the previous document in the list of documents built by navigating links.
		!fn: $forward()
		Changes the document displayed to the next document in the list of documents built by navigating links.
		!fn: $home()
		Changes the document displayed to be the first document the browser displayed.
		!fn: $reload()
		Reloads the current set source.
		!fn: $linkClickedEvent(<link_href:string>)
		Triggered when a link is clicked by the user. The default implementation of this function
		emits the "linkClicked" signal.
	@signals:
		!sg: $linkClicked(<link_href:string>)
		This signal is emitted by the default implementation of the [classfnc]$linkClickedEvent[/classfnc]() function.
*/

KVSO_BEGIN_REGISTERCLASS(KviKvsObject_textbrowser,"textbrowser","multilineedit")
	KVSO_REGISTER_HANDLER(KviKvsObject_textbrowser,"setSource",function_setSource)
	KVSO_REGISTER_HANDLER(KviKvsObject_textbrowser,"forward",function_forward)
	KVSO_REGISTER_HANDLER(KviKvsObject_textbrowser,"backward",function_backward)
	KVSO_REGISTER_HANDLER(KviKvsObject_textbrowser,"home",function_home)
	KVSO_REGISTER_HANDLER(KviKvsObject_textbrowser,"reload",function_reload)
	KVSO_REGISTER_HANDLER(KviKvsObject_textbrowser,"linkClickedEvent",function_linkClickedEvent)
KVSO_END_REGISTERCLASS(KviKvsObject_textbrowser)

KVSO_BEGIN_CONSTRUCTOR(KviKvsObject_textbrowser,KviKvsObject_mledit)

KVSO_END_CONSTRUCTOR(KviKvsObject_textbrowser)


KVSO_BEGIN_DESTRUCTOR(KviKvsObject_textbrowser)

KVSO_END_CONSTRUCTOR(KviKvsObject_textbrowser)

bool KviKvsObject_textbrowser::init(KviKvsRunTimeContext * pContext,KviKvsVariantList *pParams)
{
	SET_OBJECT(QTextBrowser);
	connect(obj,SIGNAL(anchorClicked(const QString &,const QString &)),this,SLOT(anchorClicked(const QString &,const QString &)));
	return true;
}

bool KviKvsObject_textbrowser::function_setSource(KviKvsObjectFunctionCall *c)
{
	QString szFile;
	KVSO_PARAMETERS_BEGIN(c)
		KVSO_PARAMETER("file_name",KVS_PT_STRING,0,szFile)
	KVSO_PARAMETERS_END(c)
	if(!QFile::exists(szFile))
	{
		c->warning(__tr2qs("I can't find the specified file '%Q'."),&szFile);
		return true;
	}
	QUrl url;
	url.setFileName(szFile);
	if (widget()) ((QTextBrowser *)widget())->setSource(url);
	return true;
}

bool KviKvsObject_textbrowser::function_forward(KviKvsObjectFunctionCall *c)
{
	if (widget()) ((QTextBrowser *)widget())->forward();
	return true;
}

bool KviKvsObject_textbrowser::function_backward(KviKvsObjectFunctionCall *c)
{
	if (widget()) ((QTextBrowser *)widget())->backward();
	return true;
}

bool KviKvsObject_textbrowser::function_home(KviKvsObjectFunctionCall *c)
{
	if (widget()) ((QTextBrowser *)widget())->home();
	return true;
}

bool KviKvsObject_textbrowser::function_reload(KviKvsObjectFunctionCall *c)
{
	if (widget()) ((QTextBrowser *)widget())->reload();
	return true;
}

void KviKvsObject_textbrowser::anchorClicked(const QString &szName,const QString &szLink)
{
	KviKvsVariantList parms(new KviKvsVariant(szLink));
	callFunction(this,"linkClickedEvent",0,&parms);
}

bool KviKvsObject_textbrowser::function_linkClickedEvent(KviKvsObjectFunctionCall *c)
{
	emitSignal("linkClicked",c,c->params());
	return true;
}

#ifndef COMPILE_USE_STANDALONE_MOC_SOURCES
#include "m_class_tbrowser.moc"
#endif //!COMPILE_USE_STANDALONE_MOC_SOURCES

