#include "Stdafx.h"
#include "GameNode.h"


HRESULT GameNode::init(void)
{
	return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
    _managerInit = managerInit;

    return S_OK;
}


void GameNode::release(void)
{
    if (_managerInit)
    {

    }
    ReleaseDC(_hWnd, _hdc);
}

void GameNode::update(void)
{
}

void GameNode::render(void)
{
}



