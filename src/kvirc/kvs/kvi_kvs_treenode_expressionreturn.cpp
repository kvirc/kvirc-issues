//=============================================================================
//
//   File : kvi_kvs_treenode_expressionreturn.cpp
//   Created on Fri 30 Jan 2004 01:27:09 by Szymon Stefanek
//
//   This file is part of the KVIrc IRC client distribution
//   Copyright (C) 2004 Szymon Stefanek <pragma at kvirc dot net>
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
//=============================================================================

#define __KVIRC__
#include "kvi_kvs_treenode_expressionreturn.h"
#include "kvi_kvs_treenode_expression.h"
#include "kvi_kvs_runtimecontext.h"
#include "kvi_locale.h"

KviKvsTreeNodeExpressionReturn::KviKvsTreeNodeExpressionReturn(const QChar * pLocation,KviKvsTreeNodeExpression * pExpression)
: KviKvsTreeNodeInstruction(pLocation)
{
	m_pExpression = pExpression;
	m_pExpression->setParent(this);
}

KviKvsTreeNodeExpressionReturn::~KviKvsTreeNodeExpressionReturn()
{
	delete m_pExpression;
}


void KviKvsTreeNodeExpressionReturn::contextDescription(QString &szBuffer)
{
	szBuffer = "Expression Return Evaluation";
}

void KviKvsTreeNodeExpressionReturn::dump(const char * prefix)
{
	qDebug("%s ExpressionReturn",prefix);
	QString tmp = prefix;
	tmp += "  ";
	m_pExpression->dump(tmp.utf8().data());
}

bool KviKvsTreeNodeExpressionReturn::execute(KviKvsRunTimeContext * c)
{
	return m_pExpression->evaluateReadOnly(c,c->returnValue());
}
