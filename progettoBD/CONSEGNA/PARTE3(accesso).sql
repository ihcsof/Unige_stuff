set search_path to 'socialmarket';

CREATE USER alice PASSWORD ‘alice’;
GRANT USAGE ON SCHEMA socialmarket TO alice;
CREATE USER roberto PASSWORD ‘roberto’;
GRANT USAGE ON SCHEMA socialmarket TO roberto;

GRANT SELECT,INSERT,UPDATE ON ALL TABLES IN SCHEMA socialmarket TO alice;
REVOKE UPDATE ON ACQUISTI FROM alice CASCADE;
GRANT DELETE ON APPUNTAMENTI, DONAZIONI, DONATORI, VOLONTARI, TURNI, APPARTENENZE TO alice;

GRANT SELECT ON ALL TABLES IN SCHEMA socialmarket TO roberto;
REVOKE SELECT ON VOLONTARI FROM roberto CASCADE;
GRANT UPDATE,INSERT ON APPUNTAMENTI, MERCI, INVENTARIO TO roberto;
GRANT UPDATE ON TRASPORTI TO roberto;
GRANT INSERT ON DONAZIONI, DONATORI, ACQUISTI TO roberto;

--SET role alice;
–-SET role roberto;

/*
SELECT table_name, privilege_type
FROM information_schema.role_table_grants
where grantee = 'alice'

SELECT table_name, privilege_type
FROM information_schema.role_table_grants
where grantee = ‘roberto’ */
