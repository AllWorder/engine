

void SController::registerScript(Script* script)
{
  scripts.push_back(script);
}

void SController::unregisterScript(Script* script)
{
  std::vector<Script*>::iterator i;
  i = scripts.begin();
  for (Script* c: scripts)
    if (c != script)
      i++;
  scripts.erase(i);
}

void SController::doAllScripts()
{
  for (Script* c: scripts)
    c -> execute();
}
