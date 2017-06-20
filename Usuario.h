#ifndef usuario_h_
#define usuario_h_

void TelaInicial();

void TelaLogin();

void TelaCadastro();

void TelaRecuperarSenha();

void TelaSaida();

void TelaEntradaSistema(char *usuario_sessao);

void TelaFinalizarSessao(char opcao);

int ProcuraNomeUsuario(char *username, char *nomearquivo);

void CadastrarDisciplina(char *usuario_sessao, char *nomearquivo);

void listarDisciplinas(char* nomearquivo);

#endif
