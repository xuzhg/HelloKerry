
                    /*
                    EntityTypeConfiguration targetEntity = _configurations.FirstOrDefault(e => e.ClrType == navProp.RelatedClrType) as EntityTypeConfiguration;
                    ValidateReferentialConstraint(targetEntity, navProp.ReferentialConstraint.PrincipalProperties);

                    info.DependentProperties =
                        navProp.ReferentialConstraint.PrincipalProperties.Select(property => _properties[property])
                        .OfType<IEdmStructuralProperty>().ToList();

                    //IList<NavigationPropertyConfiguration> parterNavigationProperties =
                    //    targetEntity.NavigationProperties.Where(n => n.RelatedClrType == config.ClrType).ToList();
                    EdmNavigationPropertyInfo parterInfo = new EdmNavigationPropertyInfo
                    {
                        Target = entityType,
                        //Name = parterNavigationProperties.Count == 1 ? parterNavigationProperties[0].Name : null,
                        DependentProperties =
                            navProp.ReferentialConstraint.DependentProperties.Select(property => _properties[property])
                                .OfType<IEdmStructuralProperty>()
                                .ToList()
                    };

                    entityType.AddUnidirectionalNavigation(info, parterInfo);*/


my new added test coseds.