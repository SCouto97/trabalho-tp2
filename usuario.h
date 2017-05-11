#ifndef usuario_h_
#define usuario_h_

void TelaInicial();

void TelaLogin();

void TelaCadastro();

void TelaRecuperarSenha();

void TelaSaida();

void TelaEntradaSistema(char usuario_sessao[20]);

void TelaFinalizarSessao(char opcao);

int ProcuraNomeUsuario(char username[20], char nomearquivo[20]);

void CadastrarDisciplina(char usuario_sessao[20], char nomearquivo[20]);

void listarDisciplinas(char* nomearquivo);

#endif
