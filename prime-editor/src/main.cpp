
#include "prime/entry.h"
#include "editor.h"

prime::core::Game* prime::core::createGame()
{
	return new Editor();
}
