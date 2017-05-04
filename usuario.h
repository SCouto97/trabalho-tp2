#ifndef usuario_h_
#define usuario_h_

typedef struct {
	char *nome, *senha, *perfil;
}UserInfos;

void TelaInicial();

void TelaLogin();

void TelaCadastro();

void TelaRecuperarSenha();

void TelaSaida();

#endif