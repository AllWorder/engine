

void SController::registerScript(Component* script)
{
  scripts.push_back(static_cast<Script*>(script));
}

void SController::unregisterScript(Component* script)
{
  std::vector<Script*>::iterator i;
  i = scripts.begin();
  for (Script* c: scripts)
    if (c != static_cast<Script*>(script))
      i++;
  scripts.erase(i);
}

void SController::doAllScripts()
{
  for (Script* c: scripts)
    c -> execute();
}

void SController::getDataStorageLink(DataStorage* data)
{
  dataPointer = data;
}